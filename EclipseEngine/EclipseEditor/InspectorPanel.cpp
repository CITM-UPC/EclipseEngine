#include "imgui.h"
#include "glm/glm.hpp"
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
            if (m_SelectedObject)
            {
                // Display the name of the selected object
                ImGui::Text("Selected Object: %s", m_SelectedObject->GetName().c_str());

                ImGui::Separator();

                // Render Transform controls (you already have this implemented)
                if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
                {
                    ImGui::Text("Transform");
                    ImGui::Separator();

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


                    ImGui::Separator();
                    (ImGui::Text("Mesh"));
                    ImGui::Separator();
                    bool temp = false;
                    ImGui::Checkbox("Active", &temp);
                    ImGui::SameLine();
                    ImGui::Text("File: ");
                    ImGui::Separator();
                    ImGui::Text("Draw:");
                    // Display the texture
                    GLuint textureID = m_SelectedObject.get()->GetTextureID();
                    if (textureID) {
                        ImGui::Image((void*)(intptr_t)textureID, ImVec2(128, 128)); // Adjust size as needed
                    }
                    //ImGui::Checkbox("Vertex Normals", &temp);
                    //ImGui::Checkbox("Face Normals", &temp);
                    //ImGui::SameLine();
                    //ImGui::Separator();
                    //ImGui::Text("Indexes: ");
                    //ImGui::Text("Normals: ");
                    //ImGui::Text("Vertexs: ");
                    //ImGui::Text("Faces: ");
                    //ImGui::Text("Tex coords: ");
                    //ImGui::Separator();
                    //ImGui::SliderFloat("Normals length", nullptr, 0.000f, 1.000f);
                    ImGui::Separator();

                    ImGui::Separator();
                    (ImGui::Text("Material"));
                    ImGui::Separator();
                    bool temp1;
                    ImGui::Checkbox("Active", &temp1);

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
