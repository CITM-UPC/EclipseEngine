#ifndef APP_H
#define APP_H

#include <memory>
#include <vector>
#include <string>
#include <list>

#include "EclipseEngine/Core.h"
#include "EclipseEngine/Logger.h"
#include "EclipseEngine/Camera.h"

#include "Module.h"
#include "Panel.h"
#include "PanelHandler.h"
#include "FPSpanel.h"
#include "EditorRenderer.h"

class PanelHandler;

class App
{
public:
	App(int argc, char* args[]);
	virtual ~App();

	bool Initialize();	
	bool Start();	// Called before the first frame
	bool Update();	// Called each loop iteration
	bool CleanUp();	// Called before quitting

	// used for adding new modules we are going to have
	void AddModule(Module* module, bool activate);

public:
	 PanelHandler* panelHandler = nullptr;
	 Camera* editorCamera = nullptr;
	 EditorRenderer* editorRenderer = nullptr;

private:
	// these functions are called in each llop iteration
	bool PreUpdate();
	bool DoUpdate();
	bool PostUpdate();

private:
	std::string name;

	// List of modules
	std::list<Module*> modules;
	std::shared_ptr<FPSPanel> m_fpsPanel;

	double dt = 0.0f;
	double lastFrame = 0.0f;

};

#endif // APP_H