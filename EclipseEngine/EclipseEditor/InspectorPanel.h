#ifndef INSPECTOR_PANEL_H
#define INSPECTOR_PANEL_H

#include "EclipseEngine/GameObject.h"
#include "Panel.h"
#include <vector>

class InspectorPanel : public Panel
{
public:
    InspectorPanel(const std::string& name, bool isVisible = false);;
    void Render() override;

    void SetSelectedObject(const std::shared_ptr<GameObject>& selectedObject) { m_SelectedObject = selectedObject; }
    void RenderCameraSettings(Camera* camera);

private:
	std::shared_ptr<GameObject> m_SelectedObject = nullptr;
};

#endif // INSPECTOR_PANEL_H