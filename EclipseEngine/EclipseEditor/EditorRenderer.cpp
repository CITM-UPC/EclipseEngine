#include "App.h"
#include "EditorRenderer.h"

EditorRenderer::EditorRenderer()
{
	fbo = new Framebuffer(core->window->GetWidth(), core->window->GetHeight());
}

EditorRenderer::~EditorRenderer()
{
	delete fbo;
	delete defaultShader;
	delete posShader;
	delete depthShader;
	delete normalShader;
	delete grid;
}

bool EditorRenderer::Initialize()
{
	fbo->Initialize();
	defaultShader = new Shader("Shaders/default.vert", "Shaders/default.frag");
	posShader = new Shader("Shaders/position.vert", "Shaders/position.frag");
	depthShader = new Shader("Shaders/depth.vert", "Shaders/depth.frag");
	optionShader = normalShader = new Shader("Shaders/normal.vert", "Shaders/normal.frag");
	outliningShader = new Shader("Shaders/outline.vert", "Shaders/outline.frag");
	aabbShader = new Shader("Shaders/aabb.vert", "Shaders/aabb.frag");
	glEnable(GL_CULL_FACE); // Backface culling testing
	glEnable(GL_STENCIL_TEST); // Stencil testing
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	grid = new Grid();
	return true;
}

bool EditorRenderer::PreUpdate()
{
	BeginFrame();
	return true;
}

void EditorRenderer::BeginFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo->GetFBO());
	glViewport(0, 0, fbo->GetWidth(), fbo->GetHeight());
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void EditorRenderer::Render(Scene* scene, Camera* editorCamera, std::shared_ptr<GameObject> selectedObject)
{
	if (!scene) return;

	// Normal object rendering
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Write 1 to the stencil buffer for all objects
	glStencilMask(0xFF); // Enable writing to the stencil buffer

	for (auto& object : scene->GetObjects())
	{
		glm::mat4 identity = object->transform.GetMatrix();
		object->UpdateAABB(glm::mat4(1.0f));
		if (glfwGetKey(core->window->GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
		{
			optionShader = posShader;
		}
		else if (glfwGetKey(core->window->GetWindow(), GLFW_KEY_O) == GLFW_PRESS)
		{
			optionShader = defaultShader;
		}
		else if (glfwGetKey(core->window->GetWindow(), GLFW_KEY_I) == GLFW_PRESS)
		{
			optionShader->SetFloat("near", 0.1f);
			optionShader->SetFloat("far", 100.f);
			optionShader = depthShader;
		}
		else if (glfwGetKey(core->window->GetWindow(), GLFW_KEY_U) == GLFW_PRESS)
		{
			optionShader = normalShader;
		}
		object->Draw(*optionShader, *editorCamera, identity);
		for (auto& child : object->GetChildren())
		{
			RenderAABB(child->GetAABB(), *aabbShader);
		}
	}

	if (selectedObject != nullptr)
	{
		// Calculate the world transform for the selected object
		glm::mat4 worldTransform = glm::mat4(1.0f);

		// Outlining: Second pass (draw outline)
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Only draw where stencil buffer is not 1
		glStencilMask(0x00); // Disable writing to the stencil buffer
		glDisable(GL_DEPTH_TEST); // Disable depth testing for stencil write

		selectedObject->Draw(*outliningShader, *editorCamera, selectedObject->transform.GetMatrix()); // Draw outline
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to fill mode
	}

	glStencilMask(0xFF); // Re-enable writing to stencil buffer for next frame
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Reset stencil function
	glEnable(GL_DEPTH_TEST); // Re-enable depth testing

	RenderGrid(grid, editorCamera);
	RenderGuizmo();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool EditorRenderer::CleanUp()
{
	return true;
}

void EditorRenderer::RenderGrid(Grid* grid, Camera* editorCamera)
{
	grid->Draw(editorCamera);
}

void EditorRenderer::RenderGuizmo()
{
}

void EditorRenderer::RenderAABB(AABB aabb, Shader& shader)
{
	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 corners[8] = {
	   glm::vec3(aabb.min.x, aabb.min.y, aabb.min.z),
	   glm::vec3(aabb.max.x, aabb.min.y, aabb.min.z),
	   glm::vec3(aabb.min.x, aabb.max.y, aabb.min.z),
	   glm::vec3(aabb.max.x, aabb.max.y, aabb.min.z),
	   glm::vec3(aabb.min.x, aabb.min.y, aabb.max.z),
	   glm::vec3(aabb.max.x, aabb.min.y, aabb.max.z),
	   glm::vec3(aabb.min.x, aabb.max.y, aabb.max.z),
	   glm::vec3(aabb.max.x, aabb.max.y, aabb.max.z),
	};

	GLuint indices[] = {
		0, 1, 1, 3, 3, 2, 2, 0,
		4, 5, 5, 7, 7, 6, 6, 4,
		0, 4, 1, 5, 3, 7, 2, 6,
	};

	// Use VAO/VBO to draw the wireframe
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(corners), corners, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	//aabbShader->Activate();

	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}
