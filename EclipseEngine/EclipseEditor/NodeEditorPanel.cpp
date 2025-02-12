#include "NodeEditorPanel.h"
#include <imgui.h>

NodeEditorPanel::NodeEditorPanel(const std::string& name, bool isVisible)
    : Panel(name), m_EditorContext(nullptr)
{
    SetVisible(isVisible);
    m_EditorContext = ed::CreateEditor(); // Create the node editor context
    ed::Config config;
    config.SettingsFile = nullptr;  // Prevent saving settings
    m_EditorContext = ed::CreateEditor(&config);
    ed::SetCurrentEditor(m_EditorContext);

    // Set background color
    ed::Style& style = ed::GetStyle();
    style.Colors[ed::StyleColor_Bg] = ImColor(20, 20, 20, 255);                 // Dark Gray
    style.Colors[ed::StyleColor_Grid] = ImColor(30, 30, 30, 255);               // Grid color
    style.Colors[ed::StyleColor_NodeBg] = ImColor(40, 40, 40, 255);             // Node bg
    style.Colors[ed::StyleColor_NodeBorder] = ImColor(80, 80, 80, 255);         // Node border
	style.Colors[ed::StyleColor_HovNodeBorder] = ImColor(155, 194, 130, 255);   // Hovered node border
}

NodeEditorPanel::~NodeEditorPanel()
{
    ed::DestroyEditor(m_EditorContext); // Cleanup the node editor
}

void NodeEditorPanel::Render()
{
    if (IsVisible())
    {
        ImGui::Begin(GetName().c_str(), &m_Visible);

        ImGui::Text(GetName().c_str()); // Debug

        ed::SetCurrentEditor(m_EditorContext);
        ed::Begin("Node Editor");

        // Example Node
        ed::BeginNode(1);
        ImGui::Text("Node 1");

        ed::BeginPin(2, ed::PinKind::Input);
        ImGui::Text("-> Input");
        ed::EndPin();

        ed::BeginPin(3, ed::PinKind::Output);
        ImGui::Text("Output ->");
        ed::EndPin();

        ed::EndNode();
        //ed::SetNodePosition(1, ImVec2(100, 100));  // Ensure visible position

        // Example Node
        ed::BeginNode(4);
        ImGui::Text("Node 2");

        ed::BeginPin(5, ed::PinKind::Input);
        ImGui::Text("-> Input");
        ed::EndPin();

        ed::BeginPin(6, ed::PinKind::Output);
        ImGui::Text("Output ->");
        ed::EndPin();

        ed::EndNode();

        ed::End();
        ed::SetCurrentEditor(nullptr);

        ImGui::End();
    }
}