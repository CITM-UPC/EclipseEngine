#ifndef RENDERER_H
#define RENDERER_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Scene.h"
#include "FrameBuffer.h"
#include "Shader.h"

class Renderer
{
public: 
	Renderer(Window* window);
	~Renderer();

	void Initialize();
	void BeginFrame();
	void Render(Scene* scene);
	void EndFrame();

	void CleanUp();

	Framebuffer* GetFramebuffer() { return fbo; }

private:
	Window* window;
	Framebuffer* fbo;
	Shader* defaultShader = nullptr;
};

#endif // RENDERER_H