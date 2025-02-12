#ifndef EDITOR_RENDERER_H
#define EDITOR_RENDERER_H

#include "EclipseEngine/Scene.h"
#include "EclipseEngine/Mesh.h"
#include "EclipseEngine/Material.h"
#include "EclipseEngine/Texture.h"
#include "EclipseEngine/Shader.h"
#include "EclipseEngine/Camera.h"
#include "EclipseEngine/Framebuffer.h"

#include "Grid.h"
#include "Module.h"
#include "App.h"

class EditorRenderer : public Module
{
public:
	EditorRenderer(App* application);
	~EditorRenderer();

	bool Initialize() override;
	bool PreUpdate() override;
	void BeginFrame();
	void Render(Scene* scene, Camera* editorCamera, std::shared_ptr<GameObject> selectedObject);
	bool CleanUp() override;

	Framebuffer* GetFramebuffer() { return fbo; }
	
private:
	void RenderGrid(Grid* grid, Camera* editorCamera);
	void RenderGuizmo();
	void RenderAABB(AABB aabb, Shader& shader);
	void DrawFrustum(const std::array<glm::vec3, 8>& frustumVertices, Shader& shader, const glm::mat4& view, const glm::mat4& projection);
	//void RenderLight(Light* light); // no lights for now

	Grid* grid = nullptr;
	Framebuffer* fbo = nullptr;
	Shader* defaultShader = nullptr;
	Shader* posShader = nullptr;
	Shader* depthShader = nullptr;
	Shader* normalShader = nullptr;
	Shader* outliningShader = nullptr;
	Shader* aabbShader = nullptr;
	Shader* frustumShader = nullptr;

	Shader* optionShader = nullptr;
	App* app;
};

#endif // !EDITOR_RENDERER_H
