#include "Renderer.h"

Renderer::Renderer(Window* window) : window(window)
{
	fbo = new Framebuffer(window->GetWidth(), window->GetHeight());
}

Renderer::~Renderer()
{
	CleanUp();
}

void Renderer::Initialize()
{
	fbo->Initialize();
	defaultShader = new Shader("Shaders/default.vert", "Shaders/default.frag");
	//glEnable(GL_CULL_FACE); // Backface culling testing
	//glEnable(GL_STENCIL_TEST); // Stencil testing
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void Renderer::BeginFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->GetFBO());
	glViewport(0, 0, fbo->GetWidth(), fbo->GetHeight());
	glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(Scene* scene)
{
	scene->Draw(*defaultShader);
}

void Renderer::EndFrame()
{
	glViewport(0, 0, window->GetWidth(), window->GetHeight());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::CleanUp()
{
	delete fbo;
	delete defaultShader;
}
