#ifndef HIERARCHY_PANEL_H
#define HIERARCHY_PANEL_H

#include <list>
#include <memory>
#include "Panel.h"
#include "InspectorPanel.h"
#include "ViewportPanel.h"

class GameObject;

class HierarchyPanel : public Panel 
{
public:
	HierarchyPanel(const std::string& name, bool isVisible = false);

	void Render() override;
	std::shared_ptr<GameObject> GetSelectedObject() const { return m_SelectedObject; }
	void SetInspectorPanel(InspectorPanel* inspectorPanel) { m_InspectorPanel = inspectorPanel; }
	void SetViewportPanel(ViewportPanel* viewportPanel) { m_ViewportPanel = viewportPanel; }

private:
	void RenderGameObjectTree(const std::shared_ptr<GameObject>& gameObject);

private:
	InspectorPanel* m_InspectorPanel = nullptr;
	ViewportPanel* m_ViewportPanel = nullptr;

	std::string m_Name;
	std::list<std::shared_ptr<GameObject>> m_RootObjects;
	std::shared_ptr<GameObject> m_SelectedObject = nullptr;
};

#endif // HIERARCHY_PANEL_H