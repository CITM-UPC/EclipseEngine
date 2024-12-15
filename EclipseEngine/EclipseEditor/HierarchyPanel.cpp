#include "EclipseEngine/GameObject.h"
#include "App.h"
#include "HierarchyPanel.h"
#include "PanelHandler.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "EclipseEngine/ModelLoader.h"

HierarchyPanel::HierarchyPanel(const std::string& name, bool isVisible) : Panel(name)
{
	SetVisible(isVisible);
	if (core->scene != nullptr)
	{
		m_RootObjects = core->scene->GetObjects();
	}
}

void HierarchyPanel::Render()
{
	if (!IsVisible()) return;

	ImGui::Begin(GetName().c_str(), &m_Visible);

	if (core->scene != nullptr)
	{
		m_RootObjects = core->scene->GetObjects();
	}

	if (ImGui::IsKeyPressed(ImGuiKey_MouseRight)
	&& ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup))
	{
		ImGui::OpenPopup("AddObject");
	}

	if (ImGui::BeginPopup("AddObject"))
	{
		if (ImGui::MenuItem("Add Object"))
		{
			const char* filterPatterns[1] = { "*.fbx" };
			const char* filePath = tinyfd_openFileDialog("Select Object", "", 1, filterPatterns, NULL, 0);
			if (filePath) {
				std::filesystem::path path(filePath);
				ModelLoader modelLoader;
				auto gameObject = modelLoader.LoadModel(filePath);
				gameObject->name = path.stem().string();
				core->scene->AddGameObject(gameObject);
			}
		}
		if (ImGui::MenuItem("Add Empty GameObject"))
		{
			core->scene->AddEmptyGameObject();
		}
		if (ImGui::MenuItem("Add Cube"))
		{
			core->scene->AddCube();
		}
		ImGui::EndPopup();
	}

	for (const auto& rootObject : m_RootObjects) {
		RenderGameObjectTree(rootObject);
	}
	
	ImGui::End();
}

void HierarchyPanel::RenderGameObjectTree(const std::shared_ptr<GameObject>& gameObject) {
  
    // Check if this GameObject is the selected one
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
    if (gameObject == m_SelectedObject) {
        flags |= ImGuiTreeNodeFlags_Selected; // Highlight if selected
    }

	// Create a tree node for the current game object
    if (ImGui::TreeNode(gameObject->GetName().c_str())) {  // Use a GetName() method to retrieve the object name

        // If selectable, add logic here to mark it as selected when clicked
        if (ImGui::IsItemClicked()) {
            // Handle selection (you may need to add selection logic, e.g., storing a reference to selected object)
			m_SelectedObject = gameObject;
			Logger::Log("Selected object: " + gameObject->GetName());

			if (m_InspectorPanel != nullptr) {
				m_InspectorPanel->SetSelectedObject(m_SelectedObject);
			}
			if (m_ViewportPanel != nullptr) {
				m_ViewportPanel->SetSelectedObject(m_SelectedObject);
			}
        }

		// Recursively render the children of the current game object
		for (const auto& child : gameObject->GetChildren()) {
			RenderGameObjectTree(child);
		}

        ImGui::TreePop();
    }
}