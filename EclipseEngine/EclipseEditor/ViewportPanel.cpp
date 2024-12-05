#include <imgui.h>
#include <ImGuizmo.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EclipseEngine/FrameBuffer.h"

#include "App.h"
#include "ViewportPanel.h"

enum class ManipulationOperation { IDLE, TRANSLATE, ROTATE, SCALE };
std::shared_ptr<GameObject> gameObject;

ViewportPanel::ViewportPanel(const std::string& name, Framebuffer* framebuffer, Camera* camera, bool visible)
	: Panel(name), m_Framebuffer(framebuffer), m_camera(camera)
{
    SetVisible(visible);

	m_Trans = std::make_unique<Texture>("EditorResources/trans.png", "icon", 0, GL_RGBA, GL_UNSIGNED_BYTE);
    m_Rot = std::make_unique<Texture>("EditorResources/rot.png", "icon", 0, GL_RGBA, GL_UNSIGNED_BYTE);
    m_Sca = std::make_unique<Texture>("EditorResources/sca.png", "icon", 0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void ViewportPanel::Render()
{
    if (IsVisible())
    {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse/* | ImGuiWindowFlags_NoMove*/;
        ImGui::Begin("Viewport", nullptr, windowFlags);

        bool isViewportHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup);
        if (isViewportHovered) m_camera->Inputs(core->window->GetWindow());

        // Get the available size of the viewport panel
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        int width = static_cast<int>(viewportPanelSize.x);
        int height = static_cast<int>(viewportPanelSize.y);

        // Resize the framebuffer if the panel size changes
        if (width != m_Framebuffer->GetWidth() || height != m_Framebuffer->GetHeight()) {
            m_Framebuffer->Resize(width, height);
            m_camera->width = width;
            m_camera->height = height;
        }

        // Display the framebuffer's texture
        ImVec2 viewportPosition = ImGui::GetCursorScreenPos(); // Position of the viewport in screen coordinates
        ImGui::Image((void*)(intptr_t)m_Framebuffer->GetTextureID(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

		// Drag and drop FBX files into the viewport
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MODEL_FILE"))
            {
                Logger::Log("Payload FBX received!"); // Log when payload is accepted
                if (payload->DataSize > 0)
                {
                    const char* filePath = static_cast<const char*>(payload->Data);

                    // Validate file path
                    std::filesystem::path path(filePath);
                    if (!std::filesystem::exists(path))
                    {
                        Logger::Log("File not found: " + std::string(filePath));
                    }
                    else
                    {
                        try
                        {
                            // Load the FBX file into a GameObject
                            ModelLoader modelLoader;
                            gameObject = modelLoader.LoadModel(filePath);

                            // Position the new GameObject at a default or calculated position
                            glm::vec3 dropPosition = m_camera->GetRaycastHitPoint(core->window->GetWindow());
                            gameObject->transform.SetPosition(dropPosition);

                            Logger::Log("FBX file loaded and added to scene: " + path.string());
							gameObject->name = path.stem().string();
                            core->scene->AddGameObject(gameObject);
                        }
                        catch (const std::exception& e)
                        {
                            Logger::Log("Error loading FBX into scene: " + std::string(e.what()));
                        }
                    }
                }
            }
            else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_FILE"))
            {
                if (m_SelectedObject != nullptr)
                {
                    const char* filePath = static_cast<const char*>(payload->Data);
                    Logger::Log("Texture file dropped to selected object: " + std::string(filePath));
					std::vector<Texture> textures{ Texture(filePath, "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE) };

					m_SelectedObject->AddComponent<Material>(textures);
                    // Handle texture file loading
                }
                else
                {
					Logger::Log("No object selected to apply texture to.");
                }
            }
            else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_FILE"))
            {
                const char* filePath = static_cast<const char*>(payload->Data);
                Logger::Log("Scene file dropped: " + std::string(filePath));
                // Handle scene file loading
            }
            ImGui::EndDragDropTarget();
        }

        // Position buttons at the top of the viewport
        ImGui::SetCursorScreenPos(ImVec2(viewportPosition.x + 20, viewportPosition.y + 10)); // Offset from top-left

        // Manipulation types (idle, translate, rotate, scale)
        static ManipulationOperation operation = ManipulationOperation::IDLE;

        if (isViewportHovered && !ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
            if (ImGui::IsKeyPressed(ImGuiKey_W)) operation = ManipulationOperation::TRANSLATE;
            if (ImGui::IsKeyPressed(ImGuiKey_E)) operation = ManipulationOperation::ROTATE;
            if (ImGui::IsKeyPressed(ImGuiKey_R)) operation = ManipulationOperation::SCALE;
            if (ImGui::IsKeyPressed(ImGuiKey_Q)) operation = ManipulationOperation::IDLE; // Optional: Escape to reset
        }

        // Function to set button colors based on the active state
        auto setActiveButtonColor = [](bool isActive) {
            if (isActive) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.61f, 0.76f, 0.51f, 0.75f)); // Active state color
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.8f, 0.6f, 1.0f));
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.15f, 0.75f)); // Default
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
            }
            };

        // Translate button
        setActiveButtonColor(operation == ManipulationOperation::TRANSLATE);
        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(m_Trans->textureID)), ImVec2(iconSize, iconSize))) {
            operation = (operation == ManipulationOperation::TRANSLATE) ? ManipulationOperation::IDLE : ManipulationOperation::TRANSLATE;
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine(0, iconSpacing);

        // Rotate button
        setActiveButtonColor(operation == ManipulationOperation::ROTATE);
        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(m_Rot->textureID)), ImVec2(iconSize, iconSize))) {
            operation = (operation == ManipulationOperation::ROTATE) ? ManipulationOperation::IDLE : ManipulationOperation::ROTATE;
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine(0, iconSpacing);

        // Scale button
        setActiveButtonColor(operation == ManipulationOperation::SCALE);
        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(m_Sca->textureID)), ImVec2(iconSize, iconSize))) {
            operation = (operation == ManipulationOperation::SCALE) ? ManipulationOperation::IDLE : ManipulationOperation::SCALE;
        }
        ImGui::PopStyleColor(2);

        // Gizmo manipulation (only active if not idle)
        if (operation != ManipulationOperation::IDLE) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());
            ImGuizmo::SetRect(viewportPosition.x, viewportPosition.y, width, height);

            glm::mat4 viewMatrix = m_camera->cameraMatrix;
            glm::mat4 projectionMatrix = glm::mat4(1.0f);

            if (m_SelectedObject) {
                glm::mat4 transform = m_SelectedObject->transform.GetMatrix();

                ImGuizmo::OPERATION guizmoOperation;
                switch (operation) {
                case ManipulationOperation::TRANSLATE: guizmoOperation = ImGuizmo::TRANSLATE; break;
                case ManipulationOperation::ROTATE:    guizmoOperation = ImGuizmo::ROTATE;    break;
                case ManipulationOperation::SCALE:     guizmoOperation = ImGuizmo::SCALE;     break;
                default: guizmoOperation = ImGuizmo::TRANSLATE; break; // Fallback
                }

                if (ImGuizmo::Manipulate(
                    glm::value_ptr(viewMatrix),
                    glm::value_ptr(projectionMatrix),
                    guizmoOperation,
                    ImGuizmo::LOCAL,
                    glm::value_ptr(transform)))
                {
                    m_SelectedObject->transform.SetMatrix(transform);
                }
            }
        }
        ImGui::End();
    }
}

void ViewportPanel::Resize(int width, int height)
{
    m_Framebuffer->Resize(width, height);
}