#include <GL/glew.h>
#include "Core.h"
#include "Logger.h"

Core::Core()
{
	ilInit();
	window = new Window(1500, 844, "Eclipse Engine");
	renderer = new Renderer(window);
	scene = new Scene();

    Logger::Log("Initialized Engine");
}

Core::~Core()
{
	CleanUp();
}

bool Core::Initialize()
{
    window->Initialize();
	renderer->Initialize();
	scene->Initialize();
    return true;
}

bool Core::PreUpdate()
{
	renderer->BeginFrame();
	return true;
}

bool Core::Update(double dt)
{
	if (window->ShouldClose()) return false;
	scene->Update(dt);
	renderer->Render(scene);
	return true;
}

bool Core::PostUpdate()
{
	renderer->EndFrame();
	glfwSwapBuffers(window->GetWindow());
	glfwPollEvents();
	return true;
}

void Core::CleanUp()
{
	window->CleanUp();
	renderer->CleanUp();
}