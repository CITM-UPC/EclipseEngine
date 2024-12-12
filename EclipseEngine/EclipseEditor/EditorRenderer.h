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

class EditorRenderer : public Module
{
public:
	EditorRenderer();
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
	//void RenderLight(Light* light); // no lights for now

	Grid* grid = nullptr;
	Framebuffer* fbo = nullptr;
	Shader* defaultShader = nullptr;
	Shader* posShader = nullptr;
	Shader* depthShader = nullptr;
	Shader* normalShader = nullptr;
	Shader* outliningShader = nullptr;
	Shader* aabbShader = nullptr;

	Shader* optionShader = nullptr;
};

#endif // !EDITOR_RENDERER_H
