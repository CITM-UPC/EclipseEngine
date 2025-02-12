#include <stdexcept>
#include "App.h"
#include "PanelHandler.h"
#include "MenuPanel.h"
#include "BasicPanel.h"
#include "FPSpanel.h"
#include "ConsolePanel.h"
#include "HierarchyPanel.h"
#include "SettingsPanel.h"
#include "AssetsPanel.h"
#include "InspectorPanel.h"
#include "ViewportPanel.h"
#include "NodeEditorPanel.h"
#include "GamePanel.h"

PanelHandler::PanelHandler(App* app) : app(app)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("EditorResources/SF-Pro-Text-Light.otf", 14.0f);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
}

PanelHandler::~PanelHandler() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool PanelHandler::Initialize()
{
    CustomStyle();

    ImGui_ImplGlfw_InitForOpenGL(core->window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    InitializePanels();
	return true;
}

bool PanelHandler::PreUpdate() 
{
	NewFrame();
	return true;
}

bool PanelHandler::Update(double dt) 
{
	Render();
	return true;
}

bool PanelHandler::PostUpdate()
{
	EndFrame();
	return true;
}

bool PanelHandler::CleanUp()
{
	for (auto& panel : m_Panels) {
		panel->CleanUp();
	}
	return true;
}

void PanelHandler::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void PanelHandler::Render() {

    // docking space
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));

    ImGuiWindowFlags dockspaceFlags = ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_AlwaysAutoResize | // Makes the window resize automatically
        ImGuiWindowFlags_UnsavedDocument |
        ImGuiDockNodeFlags_AutoHideTabBar /*| ImGuiWindowFlags_NoBackground*/;

    ImGui::Begin("DockSpace", nullptr, dockspaceFlags);

    // Create the dockspace node
    ImGuiID dockspaceID = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    ImGui::GetStyle().Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // Transparent background for docking

    RenderPanels();

    ImGui::PopStyleVar(3);

    ImGui::End();
}

void PanelHandler::EndFrame()
{
    // End the ImGui frame and render it
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(core->window->GetWindow());
    }
}

void PanelHandler::ShowDemoWindow(bool* p_open) {
    ImGui::ShowDemoWindow(p_open);
}

void PanelHandler::CustomStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Example style customizations
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.FramePadding = ImVec2(10, 5);
    style.ItemSpacing = ImVec2(5, 5);
    style.ScrollbarSize = 15.0f;                                            // Size of scrollbar

    // Set colors
    ImVec4* colors = ImGui::GetStyle().Colors;

    // Text
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);             // Background color for main windows
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);              // Background color for child windows/panels
    colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);              // Background color for pop-up windows

    // Headers
    colors[ImGuiCol_Header] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);               // Background color for headers (hovered or active)
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);        // Color when header is hovered
    colors[ImGuiCol_HeaderActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);         // Color when header is active

    // Borders and separators
    colors[ImGuiCol_Border] = ImVec4(0.05f, 0.05f, 0.05f, 0.7f);            // Border color
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)  ;       // Border shadow color

    // Buttons
    colors[ImGuiCol_Button] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);               // Button color
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f) ;       // Button color when hovered
    colors[ImGuiCol_ButtonActive] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);         // Button color when active

    // Frame background (used for inputs, sliders, etc.)
    colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);              // Background color for frames
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.3f, 0.35f, 1.0f);      // Frame color when hovered
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.4f, 0.4f, 0.5f, 1.0f);        // Frame color when active

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);                   // Background color for tabs
    colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);        // Tab color when hovered
    colors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);            // Tab color when active
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);         // Tab color when unfocused
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);   // Active tab color when unfocused

    // Titles
    colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);            // Background color for title bar
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);      // Title bar color when active
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);     // Title bar color when collapsed

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.1f, 0.5f);        // Background color for scrollbars
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);        // Scrollbar grab color
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); // Scrollbar grab color when hovered
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);  // Scrollbar grab color when active

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);           // Color for sliders
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);     // Color when slider is active

    // Checkmark
    colors[ImGuiCol_CheckMark] = ImVec4(0.1f, 0.9f, 0.4f, 1.0f);            // Color for checkmark

    // Separators
    colors[ImGuiCol_Separator] = ImVec4(0.48f, 0.56f, 0.56f, 1.0f);         // Separator color
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.5f, 0.5f, 0.6f, 1.0f);     // Separator color when hovered
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.6f, 0.6f, 0.7f, 1.0f);      // Separator color when active

    // Resize grip (used for resizable windows)
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.48f, 0.56f, 0.56f, 1.0f);        // Resize grip color
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.5f, 0.5f, 0.6f, 1.0f);    // Resize grip color when hovered
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.6f, 0.6f, 0.7f, 1.0f);     // Resize grip color when active

    // Plot lines and histogram
    colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);            // Color for plot lines
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.6f, 0.1f, 1.0f);     // Plot lines when hovered
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.61f, 0.76f, 0.51f, 0.75f);     // Color for histogram plots
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.8f, 0.3f, 1.0f); // Histogram color when hovered

    // Modal window darkening
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);     // Dim background for modal windows

    // Table
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);        // Background for table headers
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.4f, 0.4f, 0.5f, 1.0f);    // Strong border for tables
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.3f, 0.3f, 0.4f, 1.0f);     // Light border for tables
    colors[ImGuiCol_TableRowBg] = ImVec4(0.1f, 0.1f, 0.15f, 1.0f);          // Row background for tables
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.15f, 0.15f, 0.2f, 1.0f);      // Alternate row background for tables

    // Set the main docking background color
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.0f);       // Transparent background

    // Change the color of the docking preview area
    colors[ImGuiCol_DockingPreview] = ImVec4(0.3f, 0.3f, 0.3f, 0.5f);       // Highlight color during docking
}

void PanelHandler::InitializePanels()
{
    AddPanel(std::make_shared<MenuPanel>("Menu Panel", *this));
    AddPanel(std::make_shared<BasicPanel>("Basic Panel", false));
    AddPanel(std::make_shared<FPSPanel>("FPS Panel", false)); 
    AddPanel(std::make_shared<ConsolePanel>("Console Panel", true));
	AddPanel(std::make_shared<HierarchyPanel>("Hierarchy Panel", true));
	AddPanel(std::make_shared<SettingsPanel>("Settings Panel", false));
    AddPanel(std::make_shared<AssetsPanel>("Assets Panel", true));
    AddPanel(std::make_shared<InspectorPanel>("Inspector Panel", true));
    AddPanel(std::make_shared<NodeEditorPanel>("Node Editor Panel", true));
    AddPanel(std::make_shared<GamePanel>("Game Panel", core->renderer->GetFramebuffer(), core->scene->GetActiveCamera(), true)); // this is the game viewport
    AddPanel(std::make_shared<ViewportPanel>("Viewport Panel", app->editorRenderer->GetFramebuffer(), app->editorCamera, true)); // this is the editor viewport

	// Set the inspector panel for the hierarchy panel
	hierarchyPanel = static_cast<HierarchyPanel*>(GetPanel("Hierarchy Panel").get());
	hierarchyPanel->SetInspectorPanel(static_cast<InspectorPanel*>(GetPanel("Inspector Panel").get()));
	hierarchyPanel->SetViewportPanel(static_cast<ViewportPanel*>(GetPanel("Viewport Panel").get()));

	viewportPanel = static_cast<ViewportPanel*>(GetPanel("Viewport Panel").get());
}

void PanelHandler::AddPanel(std::shared_ptr<Panel> panel) {
    m_Panels.push_back(std::move(panel));
}

void PanelHandler::RenderPanels() {
    for (const auto& panel : m_Panels) {
        panel->Render();
    }
}

bool PanelHandler::TogglePanel(const std::string& name) {
    for (auto& panel : m_Panels) {
        if (panel->GetName() == name) {
            panel->SetVisible(!panel->IsVisible());
            return panel->IsVisible(); // Return new visibility state
        }
    }
    return false;
}

bool PanelHandler::GetPanelVisibility(const std::string& name) {
    for (const auto& panel : m_Panels) {
        if (panel->GetName() == name) {
            return panel->IsVisible();
        }
    }
    return false;
}

std::shared_ptr<Panel> PanelHandler::GetPanel(const std::string& name) {
    for (auto& panel : m_Panels) {
        if (panel->GetName() == name) {
            return panel;
        }
    }
    throw std::runtime_error("Panel not found: " + name);
}