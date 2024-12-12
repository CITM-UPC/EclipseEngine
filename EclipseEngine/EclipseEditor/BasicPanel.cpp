#include "BasicPanel.h"
#include <imgui.h>

BasicPanel::BasicPanel(const std::string& name, bool isVisible) : Panel(name)
{
    SetVisible(isVisible);
}

void BasicPanel::Render() {
    if (IsVisible())
    {
        ImGui::Begin(GetName().c_str(), &m_Visible);
        ImGui::Text("Usar este codigo como referencia");
        ImGui::End();
    }
}