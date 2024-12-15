#include "imgui.h"
#include "glm/glm.hpp"
#include "App.h"
#include "InspectorPanel.h"
#include "tinyfiledialogs.h"

InspectorPanel::InspectorPanel(const std::string& name, bool isVisible) : Panel (name)
{
    SetVisible(isVisible);
}

void InspectorPanel::Render()
{
    if (IsVisible())
    {
        ImGui::Begin(GetName().c_str(), &m_Visible);


        if(ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {   
            if (m_SelectedObject != nullptr)
            {
                // Display the name of the selected object
                ImGui::Text("Selected Object: %s", m_SelectedObject->GetName().c_str());

                ImGui::Separator();

                // Render Transform controls (you already have this implemented)
                if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
                {
                    ImGui::Text("TRANSFORM");

                    // Position
                    glm::vec3 position = m_SelectedObject->transform.position;
                    if (ImGui::SliderFloat3("Position", &position.x, -100.0f, 100.0f))
                    {
                        m_SelectedObject->transform.SetPosition(position);
                    }
                    // Scale
                    glm::vec3 scale = m_SelectedObject.get()->transform.scale;
                    if (ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 10.0f))
                    {
                        m_SelectedObject->transform.SetScale(scale);
                    }
                    // Rotation (in degrees for display)
                    glm::quat rotationQuat = m_SelectedObject->transform.rotation;
                    glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(rotationQuat));
                    // Update Euler angles directly in degrees (for user input)
                    if (ImGui::SliderFloat3("Rotation", &eulerRotation.x, -180.0f, 180.0f)) 
                    {
                        // Convert the updated Euler angles back to a quaternion
                        rotationQuat = glm::quat(glm::radians(eulerRotation));
                        m_SelectedObject->transform.SetRotation(rotationQuat);
                    }

                    // Add Component button with selection menu
                    if (ImGui::Button("Add Component"))
                    {
                        ImGui::OpenPopup("AddComponentPopup");
                    }

                    if (ImGui::BeginPopup("AddComponentPopup"))
                    {
                        if (ImGui::MenuItem("Mesh"))
                        {
                            //m_SelectedObject->AddComponent<Mesh>();
                        }
                        if (ImGui::MenuItem("Material"))
                        {
                            //m_SelectedObject->AddComponent<Material>();
                        }
                        if (ImGui::MenuItem("Camera"))
                        {
                            m_SelectedObject->AddComponent<Camera>(1500, 844, m_SelectedObject->transform.position);
                        }
                        ImGui::EndPopup();
                    }

                    ImGui::SameLine(0.0f, 1.0f);
					if (m_SelectedObject->components.size() > 0)
					{
                        // Remove Component button with selection menu
                        if (ImGui::Button("Remove Component"))
                        {
                            ImGui::OpenPopup("RemoveComponentPopup");
                        }
					} 

                    if (ImGui::BeginPopup("RemoveComponentPopup"))
                    {
                        if (m_SelectedObject->GetComponent<Mesh>() && ImGui::MenuItem("Mesh"))
                        {
                            m_SelectedObject->RemoveComponent<Mesh>();
                        }
                        if (m_SelectedObject->GetComponent<Material>() && ImGui::MenuItem("Material"))
                        {
                            m_SelectedObject->RemoveComponent<Material>();
                        }
                        if (m_SelectedObject->GetComponent<Camera>() && ImGui::MenuItem("Camera"))
                        {
                            m_SelectedObject->RemoveComponent<Camera>();
                        }
                        ImGui::EndPopup();
                    }

                    if (m_SelectedObject->GetComponent<Mesh>()) {
                        ImGui::Separator();
                        (ImGui::Text("MESH"));
                        bool temp = true;
                        ImGui::Checkbox("Active", &temp);
						ImGui::Text("Vertices: %d", m_SelectedObject->GetComponent<Mesh>()->vertices.size());
                        ImGui::SameLine(0, 20);
						ImGui::Text("Indices: %d", m_SelectedObject->GetComponent<Mesh>()->indices.size());
                    }

                    if (m_SelectedObject->GetComponent<Material>()) {
                        ImGui::Separator();
                        (ImGui::Text("MATERIAL"));

                        (ImGui::Text("Texture Preview:"));
                        // Display the texture
                        GLuint textureID = m_SelectedObject.get()->GetTextureID();
                        if (textureID) {
                            ImGui::Image((void*)(intptr_t)textureID, ImVec2(256, 256));
                        }
                    }

                    if (m_SelectedObject->GetComponent<Camera>()) {
						if (ImGui::Checkbox("Active", &m_SelectedObject->GetComponent<Camera>()->mainCamera)) {
							core->scene->SetActiveCamera(m_SelectedObject->GetComponent<Camera>());
                        }
						if (ImGui::SliderFloat("FOV", &m_SelectedObject->GetComponent<Camera>()->FOVdeg, 1.0f, 179.0f))
						{
							//m_SelectedObject->GetComponent<Camera>()->UpdateProjectionMatrix();
						}
                        if (ImGui::SliderFloat("Near Plane", &m_SelectedObject->GetComponent<Camera>()->nearPlane, 0.1f, 100.0f));
						if (ImGui::SliderFloat("Far Plane", &m_SelectedObject->GetComponent<Camera>()->farPlane, 0.1f, 100.0f));
                    }
                    ImGui::Separator();
                    if (ImGui::Button("Delete Object")) {
                        core->scene->DeleteGameObject(m_SelectedObject);
                        m_SelectedObject = nullptr;
                    }

                    ImGui::EndTabBar();
                }
            }
            else
            {
                // Display a placeholder message when no object is selected
                ImGui::Text("No object selected.");
            }

            
            ImGui::EndTabBar();
        }
        ImGui::End();
    }
    
}
