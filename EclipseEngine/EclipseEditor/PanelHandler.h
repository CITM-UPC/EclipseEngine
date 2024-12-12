#ifndef PANELHANDLER_H
#define PANELHANDLER_H

#include <string>
#include <vector>
#include <memory> // For std::unique_ptr

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Panel.h"
#include "Module.h"
#include "HierarchyPanel.h"

class PanelHandler : public Module
{
public:
    PanelHandler(App* app);
    ~PanelHandler();

	bool Initialize() override;
    bool PreUpdate() override;
    bool Update(double dt) override;
    bool PostUpdate() override;
	bool CleanUp() override;

    void NewFrame();
    void Render();
    void EndFrame();
    void ShowDemoWindow(bool* p_open);
    void CustomStyle();

    // Panel management
    void InitializePanels();
    void AddPanel(std::shared_ptr<Panel> panel);
    void RenderPanels();
    bool TogglePanel(const std::string& name);
    bool GetPanelVisibility(const std::string& name);

    std::shared_ptr<Panel> GetPanel(const std::string& name);
	HierarchyPanel* hierarchyPanel;

private:
    std::vector<std::shared_ptr<Panel>> m_Panels;
    App* app;
};

#endif // PANELHANDLER_H