#include "../EclipseEngine/Camera.h"
#include "App.h"
#include <GLFW/glfw3.h>
#include "MenuPanel.h"
#include <imgui.h>
#include "EclipseEngine/Logger.h"
#include <windows.h>

MenuPanel::MenuPanel(const std::string& name, PanelHandler& panelHandler)
    : Panel(name), m_PanelHandler(panelHandler) {}

void MenuPanel::Render() {
    if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			bool _new = false;
			ImGui::MenuItem("New", nullptr, _new);
			ImGui::MenuItem("Open", nullptr, nullptr);
			ImGui::MenuItem("Save", nullptr, nullptr);
			ImGui::MenuItem("Save As", nullptr, nullptr);
			ImGui::EndMenu();
		}
        if (ImGui::BeginMenu("Panels")) {
            bool isBasicPanelVisible = m_PanelHandler.GetPanelVisibility("Basic Panel"); // Check visibility
            ImGui::MenuItem("Basic Panel", nullptr, &isBasicPanelVisible);
            if (isBasicPanelVisible != m_PanelHandler.GetPanelVisibility("Basic Panel")) {
                m_PanelHandler.TogglePanel("Basic Panel"); // Toggle the Basic Panel's visibility
            }

            // Toggle for the FPS panel
            bool isFPSPanelVisible = m_PanelHandler.GetPanelVisibility("FPS Panel");
            ImGui::MenuItem("FPS Panel", nullptr, &isFPSPanelVisible);
            if (ImGui::IsItemClicked()) {
                m_PanelHandler.TogglePanel("FPS Panel");
            }

			// Toggle for the Hierarchy panel
			bool isHierarchyPanelVisible = m_PanelHandler.GetPanelVisibility("Hierarchy Panel");
			ImGui::MenuItem("Hierarchy Panel", nullptr, &isHierarchyPanelVisible);
			if (ImGui::IsItemClicked()) {
				m_PanelHandler.TogglePanel("Hierarchy Panel");
			}

			// Toggle for the Console panel
			bool isConsolePanelVisible = m_PanelHandler.GetPanelVisibility("Console Panel");
			ImGui::MenuItem("Console Panel", nullptr, &isConsolePanelVisible);
			if (ImGui::IsItemClicked()) {
				m_PanelHandler.TogglePanel("Console Panel");
			}

			// Toggle node editor
			bool isNodePanelVisible = m_PanelHandler.GetPanelVisibility("Node Editor Panel");
			ImGui::MenuItem("Node Editor Panel", nullptr, &isNodePanelVisible);
			if (ImGui::IsItemClicked()) {
				m_PanelHandler.TogglePanel("Node Editor Panel");
			}

            ImGui::EndMenu();
        }

		if (ImGui::BeginMenu("Windows")) {
			bool isScenePanelVisible = m_PanelHandler.GetPanelVisibility("Viewport Panel");
			ImGui::MenuItem("Viewport", nullptr, &isScenePanelVisible);
			if (isScenePanelVisible != m_PanelHandler.GetPanelVisibility("Viewport Panel")) {
				m_PanelHandler.TogglePanel("Viewport Panel");
			}

			bool isInspectorPanelVisible = m_PanelHandler.GetPanelVisibility("Inspector Panel");
			ImGui::MenuItem("Inspector Panel", nullptr, &isInspectorPanelVisible);
			if (isInspectorPanelVisible != m_PanelHandler.GetPanelVisibility("Inspector Panel")) {
				m_PanelHandler.TogglePanel("Inspector Panel");
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) {
			ImGui::MenuItem("Options", nullptr, nullptr);
			bool isSettingsPanelVisible = m_PanelHandler.GetPanelVisibility("Settings Panel");
			if (ImGui::BeginTabBar("Settings"))
			{
				if (ImGui::BeginTabItem("Display"))
				{
					//Window
					if (ImGui::CollapsingHeader("Window")) {
						/*int width = App->window->GetWidth();
						int height = App->window->GetHeight();*/
						int width;
						int height;
						glfwGetWindowSize(core->window->GetWindow() , &width, &height);
						if (ImGui::SliderInt("Width", &width, 256, 4096) || ImGui::SliderInt("Height", &height, 144, 2160)) {
							//App->window->ResizeWindow(width, height);
							Logger::Log("screen size modified");
							glfwSetWindowSize(core->window->GetWindow(), width, height);
						}

						//float brightness = App->window->GetBrightness();
						float brightness = 1.0f;
						if (ImGui::SliderFloat("Brightness", &brightness, 0.000f, 1.000f)) {
							//App->window->ChangeWindowBrightnessTo(brightness);
						}

						float opacity = 1.0f;
						if (ImGui::SliderFloat("Opacity", &opacity, 0.000f, 1.000f)) {
							Logger::Log("screen opacity modified");
							glfwSetWindowOpacity(core->window->GetWindow(), opacity);
						}

						//bool temp = App->window->GetFullscreen();
						bool temp = false;
						if (ImGui::Checkbox("Fullscreen", &temp)) {
							//App->window->WindowSetFullscreen(temp);

							if (temp) {
								Logger::Log("Toggled fullscreen");
								glfwSetWindowMonitor(core->window->GetWindow(), nullptr, 0, 0, GL_MAX_WIDTH, GL_MAX_HEIGHT, GLFW_DONT_CARE);
							}							
						}

						ImGui::SameLine();
						//temp = App->window->GetResizable();
						if (ImGui::Checkbox("Resizable", &temp)) {
							//App->window->WindowSetResizable(temp);

						}

						ImGui::SameLine();
						//temp = App->window->GetBorderless();
						if (ImGui::Checkbox("Borderless", &temp)) {
							//App->window->WindowSetBorderless(temp);
						}

						ImGui::SameLine();
						//temp = App->window->GetFullDesktop();
						if (ImGui::Checkbox("Full Desktop", &temp)) {
							//App->window->WindowSetFullscreenDesktop(temp);
							glfwSetWindowSize(core->window->GetWindow(), GL_MAX_WIDTH, GL_MAX_HEIGHT);
							
						}
					}

					//Plotting FPS and ms
					if (ImGui::CollapsingHeader("Framerate")) {

						int max_fps = 60;
						//ImGui::SliderInt("MAX FPS", &App->max_FPS, -1, 120);
						ImGui::SliderInt("MAX FPS", &max_fps, -1, 120);
						ImGui::SameLine();
						bool vsync = false;
						if (ImGui::Checkbox("VSync", /*&App->renderer3D->vSync*/ &vsync)) {
							//if (App->renderer3D->vSync) {
							if (false) {
								//SDL_GL_SetSwapInterval(1);
							}
							else {
								//SDL_GL_SetSwapInterval(0);
							}
						}

						//char title[25];
						//sprintf_s(title, 25, "Framerate %.1f", App->fps_log[App->fps_log.size() - 1]);
						//ImGui::PlotHistogram("##framerate", &App->fps_log[0], App->fps_log.size(), 0, title, 0.0f, 140.0f, ImVec2(310, 100));
						//sprintf_s(title, 25, "Milliseconds %.1f", App->ms_log[App->ms_log.size() - 1]);
						//ImGui::PlotHistogram("##milliseconds", &App->ms_log[0], App->ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
					}

					// Editor Camera
					if (ImGui::CollapsingHeader("Camera")) {
						//ComponentCamera* camPtr = App->camera->GetActiveCamera();
						//float tempf;
						//
						//tempf = camPtr->GetNearPlaneDist();
						//if (ImGui::SliderFloat("Near Plane", &tempf, 0.1f, App->camera->GetActiveCamera()->GetFarPlaneDist())) App->camera->GetActiveCamera()->SetNearPlaneDist(tempf);
						//tempf = camPtr->GetFarPlaneDist();
						//if (ImGui::SliderFloat("Far Plane", &tempf, App->camera->GetActiveCamera()->GetNearPlaneDist(), 5000.f)) App->camera->GetActiveCamera()->SetFarPlaneDist(tempf);
						//
						//ImGui::Separator();
						//
						//tempf = camPtr->GetFOV();
						//if (ImGui::SliderFloat("Field of View", &tempf, 1.f, 180.f)) App->camera->GetActiveCamera()->SetFOV(tempf);
						//tempf = camPtr->GetAspectRatio();
						//if (ImGui::SliderFloat("Aspect Ratio", &tempf, 0.1f, 10.f)) App->camera->GetActiveCamera()->SetAspectRatio(tempf);
					}

					ImGui::EndTabItem();
				}

				// Controls Tab
				if (ImGui::BeginTabItem("Controls"))
				{
					// Editor Camera
					if (ImGui::CollapsingHeader("Camera")) {
						ImGui::Text("Keyboard Inputs");
						//ImGui::SliderFloat("Movement Speed", &App->camera->camMovSpeed, App->camera->camDefaultMin, App->camera->maxMovSpeed);
						//ImGui::SliderFloat("Movement Multiplier", &App->camera->camMovMultiplier, App->camera->camDefaultMin, App->camera->maxMovMultiplier);

						ImGui::Separator();

						ImGui::Text("Mouse Inputs");
						//ImGui::SliderFloat("Mouse Sensibility", &App->camera->mouseSens, App->camera->camDefaultMin, App->camera->maxMouseSens);
						//ImGui::SliderFloat("Scroll Sensibility", &App->camera->scrollSens, App->camera->camDefaultMin, App->camera->maxScrollSens);
					}

					// Input Data
					if (ImGui::CollapsingHeader("Input Data")) {
						ImGui::Text("Mouse Position: "); 
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.0f), "%d, %d", App->input->GetMouseX(), App->input->GetMouseY());

						ImGui::Text("Mouse Motion: "); 
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.0f), "%d, %d", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

						ImGui::Text("Mouse Wheel: "); 
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.0f), "%d", App->input->GetMouseZ());

						ImGui::Text("Input Log");

						// Scrollbar TEST
						//static bool disable_mouse_wheel = false;
						//static bool disable_menu = false;
						//ImGui::Checkbox("Disable Mouse Wheel", &disable_mouse_wheel);
						//ImGui::Checkbox("Disable Menu", &disable_menu);
						//
						//static int line = 50;
						//bool goto_line = ImGui::Button("Goto");
						//ImGui::SameLine();
						//ImGui::SetNextItemWidth(100);
						//goto_line |= ImGui::InputInt("##Line", &line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);
						//
						//ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar | (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0);
						//ImGui::BeginChild("Child1", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 260), false, window_flags);
						//if (App->input->input_log.size() > 0)
						//{
						//	int i = 0;
						//	while (i != App->input->input_log.size())
						//	{
						//		//ImGui::Text("%04d: scrollable region", i);
						//		ImGui::Text("Key: %d %s", App->input->input_log[i], App->input->input_type_log[i]);
						//		if (goto_line && line == i)
						//			ImGui::SetScrollHereY();
						//		++i;
						//	}
						//	if (goto_line && line >= 100)
						//		ImGui::SetScrollHereY();
						//}
						//ImGui::EndChild();
					}

					ImGui::EndTabItem();
				}

				// Renderer Tab
				if (ImGui::BeginTabItem("Renderer")) {

					//Refresh rate
					ImGui::Text("Refresh rate: ");
					ImGui::SameLine();
					//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.00f), "%.1f", App->fps_log[App->fps_log.size() - 1]);

					ImGui::Separator();

					//GL_Settings
					ImGui::Text("OpenGL Options");

					ImGui::BulletText("General");

					//if (ImGui::Checkbox("Depth Test", &App->renderer3D->GL_DepthTest.status))
						//App->renderer3D->SwitchGLSetting(App->renderer3D->GL_DepthTest);

					ImGui::SameLine();

					//if (ImGui::Checkbox("Cull Face", &App->renderer3D->GL_CullFace.status))
						//App->renderer3D->SwitchGLSetting(App->renderer3D->GL_CullFace);

					ImGui::SameLine();

					//if (ImGui::Checkbox("Lightning", &App->renderer3D->GL_Lighting.status))
						//App->renderer3D->SwitchGLSetting(App->renderer3D->GL_Lighting);

					//------------------------------------------------------------

					ImGui::BulletText("Textures");

					/*if (ImGui::RadioButton("2D", &App->editor->textureMode, (int)texture_mode::TWO_D)) {
						App->editor->TextureModeChange();
					}*/

					ImGui::SameLine();

					/*if (ImGui::RadioButton("Cube Map", &App->editor->textureMode, (int)texture_mode::CUBEMAP)) {
						App->editor->TextureModeChange();
					}*/

					//------------------------------------------------------------

					ImGui::BulletText("Points & Lines");

					/*if (ImGui::Checkbox("Point Smooth", &App->renderer3D->GL_PointSmooth.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_PointSmooth);

					ImGui::SameLine();

					if (ImGui::Checkbox("Line Smooth", &App->renderer3D->GL_LineSmooth.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_LineSmooth);

					ImGui::SameLine();

					if (ImGui::Checkbox("Line Stipple", &App->renderer3D->GL_LineStipple.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_LineStipple);

					//------------------------------------------------------------

					ImGui::BulletText("Polygons");

					if (ImGui::Checkbox("Polygon Smooth", &App->renderer3D->GL_PolygonSmooth.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_PolygonSmooth);

					ImGui::SameLine();

					if (ImGui::Checkbox("Polygon Stipple", &App->renderer3D->GL_PolygonStipple.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_PolygonStipple);

					//------------------------------------------------------------

					ImGui::BulletText("Color");

					if (ImGui::Checkbox("Blend", &App->renderer3D->GL_Blend.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_Blend);

					ImGui::SameLine();

					if (ImGui::Checkbox("Dither", &App->renderer3D->GL_Dither.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_Dither);

					//------------------------------------------------------------

					if (ImGui::Checkbox("Color Material", &App->renderer3D->GL_ColorMaterial.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_ColorMaterial);

					ImGui::SameLine();

					if (ImGui::Checkbox("MinMax", &App->renderer3D->GL_MinMax.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_MinMax);

					ImGui::SameLine();

					if (ImGui::Checkbox("Multi Sample", &App->renderer3D->GL_MultiSample.status))
						App->renderer3D->SwitchGLSetting(App->renderer3D->GL_MultiSample);*/

					ImGui::EndTabItem();
				}

				// Hardware Tab
				if (ImGui::BeginTabItem("System"))
				{
					if (ImGui::CollapsingHeader("Software")) {
						ImGui::Text("SDL: ");
						ImGui::BulletText("Version: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 0.0f, 255.0f, 255.00f), "%d.%d.%d", (int)App->hardware.sdl_version.major, (int)App->hardware.sdl_version.minor, (int)App->hardware.sdl_version.patch);

						ImGui::Text("OpenGL: ");
						ImGui::BulletText("Version: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(0.0f, 255.0f, 0.0f, 255.00f), "%s", App->hardware.GPU.version);

						ImGui::BulletText("Vendor: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(0.0f, 255.0f, 0.0f, 255.00f), "%s", App->hardware.GPU.vendor);

						ImGui::Text("DevIL: ");
						ImGui::BulletText("Version: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 255.00f), "%s", App->hardware.devil_info.version);

						ImGui::BulletText("Vendor: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 255.00f), "%s", App->hardware.devil_info.vendor);
						ImGui::Separator();
					}

					if (ImGui::CollapsingHeader("Hardware")) {

						ImGui::Text("CPU: ");

						ImGui::BulletText("Cores: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(0.0f, 255.0f, 255.0f, 255.00f), "%d", App->hardware.CPU_logic_cores);

						ImGui::BulletText("Includes Features: ");
						/*for (int i = 0; i < App->CPU_features.size(); ++i)
						{
							ImGui::TextColored(ImVec4(0.0f, 255.0f, 255.0f, 255.0f), "%s,", App->CPU_features[i].data());
							if (i == 0 || (float)(i % 4) != 0.0f)
								ImGui::SameLine();
						}*/

						ImGui::Separator();

						ImGui::Text("GPU: ");
						ImGui::BulletText("Renderer: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(0.0f, 255.0f, 0.0f, 255.00f), "%s", App->hardware.GPU.renderer);

						ImGui::Separator();

						ImGui::Text("RAM: ");

						ImGui::SameLine(250);
						/*if (ImGui::RadioButton("KB", &App->editor->byteSizeMode, (int)byte_size_mode::KB)) {
							App->editor->ByteSizeModeChange();
						}
						ImGui::SameLine();
						if (ImGui::RadioButton("MB", &App->editor->byteSizeMode, (int)byte_size_mode::MB)) {
							App->editor->ByteSizeModeChange();
						}
						ImGui::SameLine();
						if (ImGui::RadioButton("GB", &App->editor->byteSizeMode, (int)byte_size_mode::GB)) {
							App->editor->ByteSizeModeChange();
						}*/

						ImGui::BulletText("RAM: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.00f), "%f %s", (float)(App->hardware.RAM * App->editor->byteAlt), App->editor->byteText.c_str());

						ImGui::Text("VRAM: ");
						ImGui::BulletText("VRAM Budget: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.00f), "%f %s", (float)(App->hardware.GPU.VRAM.budget * App->editor->byteAlt), App->editor->byteText.c_str());

						ImGui::BulletText("VRAM Usage: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.00f), "%f %s", (float)(App->hardware.GPU.VRAM.usage * App->editor->byteAlt), App->editor->byteText.c_str());

						ImGui::BulletText("VRAM Available: ");
						ImGui::SameLine();
						//ImGui::TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.00f), "%f %s", (float)(App->hardware.GPU.VRAM.available * App->editor->byteAlt), App->editor->byteText.c_str());

						//ImGui::BulletText("VRAM Reserved: ");	//CHANGE/FIX: Until this has an actual value it will remain commented
					}

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("About", nullptr, nullptr);
			if (ImGui::MenuItem("GitHub")) {
				// Open the GitHub repository in the default web browser
				const char* url = "https://github.com/migon25/EclipseEngine";
				#if defined(_WIN32)
				ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
				#elif defined(__APPLE__)
				std::string openUrlCommand = "open " + std::string(url);
				system(openUrlCommand.c_str());
				#elif defined(__linux__)
				std::string openUrlCommand = "xdg-open " + std::string(url);
				system(openUrlCommand.c_str());
				#endif
			}

			ImGui::EndMenu();
		}

		// Render start/pause/stop buttons in the center
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - 50, ImGui::GetWindowHeight() / 2 - 10));
		if (ImGui::Button("Start")) {
			m_SystemState = SystemState::Running;
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause")) {
			m_SystemState = SystemState::Paused;
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop")) {
			m_SystemState = SystemState::Stopped;
		}

		// Display the current state
		ImGui::Text("Current State: %s",
			m_SystemState == SystemState::Stopped ? "Stopped" :
			m_SystemState == SystemState::Running ? "Running" : "Paused");

        ImGui::EndMainMenuBar();
    }

}
