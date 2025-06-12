#ifndef MENU_PANEL_H
#define MENU_PANEL_H

#include "EclipseEngine/Texture.h"

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

private:
    std::unique_ptr<Texture> play;
    std::unique_ptr<Texture> pause;
    std::unique_ptr<Texture> stop;
};

#endif // MENU_PANEL_H