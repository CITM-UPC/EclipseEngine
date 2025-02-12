#include "EclipseEngine/Logger.h"
#include "App.h"

Core* core = NULL;

App::App(int argc, char* args[])
{
	core = new Core();
	panelHandler = new PanelHandler(this);
	editorCamera = new Camera(core->window->GetWidth(), core->window->GetHeight(), glm::vec3(38.0f, 20.0f, -37.0f));
	editorRenderer = new EditorRenderer(this);

	AddModule(editorRenderer, true);
	AddModule(panelHandler, true);
}

App::~App()
{
}

bool App::Initialize()
{
	if(!core->Initialize()) return false;
	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if (!(*it)->Initialize()) return false;
	}
	m_fpsPanel = std::dynamic_pointer_cast<FPSPanel>(panelHandler->GetPanel("FPS Panel"));
	return true;
}

bool App::Start()
{
	Initialize();
	return true;
}

bool App::Update()
{
	float currentFrame = glfwGetTime();
	dt = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float fps = 1.0f / dt;          // Assuming dt is the delta time (time since last frame in seconds)
	float ms = dt * 1000.0f;        // Convert delta time to milliseconds

	if (m_fpsPanel) {
		if (auto fpsPanel = dynamic_cast<FPSPanel*>(m_fpsPanel.get())) {
				fpsPanel->Update(fps, ms);
		}
	}

	// Pass these values to the FPS panel
	if (!PreUpdate()) return false;
	if (!DoUpdate()) return false;
	if (!PostUpdate()) return false;
	return true;
}

bool App::CleanUp()
{
	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		(*it)->CleanUp();
	}
	core->CleanUp();
	return true;
}

void App::AddModule(Module* module, bool activate)
{
	if (activate) module->Enable();
	modules.push_back(module);
}

bool App::PreUpdate()
{
	editorCamera->UpdateMatrix(0.1f, 200.0f);
	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if ((*it)->active == false) continue;
		if (!(*it)->PreUpdate()) return false;
	}
	editorRenderer->Render(core->scene, editorCamera, panelHandler->hierarchyPanel->GetSelectedObject());
	if (!core->PreUpdate()) return false;
	return true;
}

bool App::DoUpdate()
{
	if (!core->Update(dt)) return false;
	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if ((*it)->active == false) continue;
		if (!(*it)->Update(dt)) return false;
	}
	return true;
}

bool App::PostUpdate()
{
	if (!core->PostUpdate()) return false;
	for (std::list<Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if ((*it)->active == false) continue;
		if (!(*it)->PostUpdate()) return false;
	}

	return true;
}
