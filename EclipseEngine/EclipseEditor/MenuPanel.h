#ifndef MENU_PANEL_H
#define MENU_PANEL_H

#include "Panel.h"
#include "PanelHandler.h" // PanelHandler for toggling panels
#include "HierarchyPanel.h"

enum class SystemState {
    Stopped,
    Running,
    Paused
};

class MenuPanel : public Panel
{
public:
    MenuPanel(const std::string& name, PanelHandler& panelHandler);

    void Render() override;

    bool demo = true;

    PanelHandler& m_PanelHandler; // Reference to PanelHandler
    SystemState m_SystemState = SystemState::Stopped;
};

#endif // MENU_PANEL_H