#include "FPSpanel.h"
#include <imgui.h>

FPSPanel::FPSPanel(const std::string& name, bool isVisible) : Panel(name), m_FPSBuffer(BUFFER_SIZE, 0.0f), m_MSBuffer(BUFFER_SIZE, 0.0f)
{
    SetVisible(isVisible);
}

void FPSPanel::Render() 
{
    if (!IsVisible()) return;

    ImGui::Begin(GetName().c_str(), &m_Visible);

    // Render FPS Histogram
    ImGui::Text("FPS");
    ImGui::PlotHistogram("##FPSHistogram", m_FPSBuffer.data(), BUFFER_SIZE, m_CurrentIndex, nullptr, 0.0f, 120.0f, ImVec2(0, 80));

    // Render Milliseconds Histogram
    ImGui::Text("Milliseconds per Frame");
    ImGui::PlotHistogram("##MSHistogram", m_MSBuffer.data(), BUFFER_SIZE, m_CurrentIndex, nullptr, 0.0f, 50.0f, ImVec2(0, 80));

    ImGui::End();
}

void FPSPanel::Update(float fps, float ms) 
{
    m_FPSBuffer[m_CurrentIndex] = fps;
    m_MSBuffer[m_CurrentIndex] = ms;
    m_CurrentIndex = (m_CurrentIndex + 1) % BUFFER_SIZE;
}