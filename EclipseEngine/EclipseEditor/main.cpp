#include "App.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <stdlib.h>

enum MainState
{
	CREATE = 1,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{
	MainState state = CREATE;
	int result = EXIT_FAILURE;

	while (state != EXIT)
	{
		//OPTICK_FRAME("MainLoop");
		switch (state)
		{
			// Allocate the engine ---------------------------------------------
		case CREATE:

			app = new App(argc, args);

			if (app != NULL)
				state = START;
			else
				state = FAIL;

			break;

			// Call all modules before first frame  ----------------------------
		case START:
			if (app->Start() == true)
			{
				state = LOOP;
			}
			else
			{
				state = FAIL;
			}
			break;

			// Loop all modules until we are asked to leave --------------------
		case LOOP:
		{
			if (app->Update() == false)
			{
				state = CLEAN;
			}
		}
		break;

		// Cleanup all modules ----------------------------------------------
		case CLEAN:
			if (app->CleanUp() == true)
			{
				state = EXIT;
				result = EXIT_SUCCESS;
			}
			else
			{
				state = FAIL;
			}
			break;

			// Something went wrong ---------------------------------------------
		case FAIL:
			state = EXIT;
			result = EXIT_FAILURE;
			break;

			// Exit the application ---------------------------------------------
		case EXIT:
			break;
		}

	}

	return result;
}

#pragma region old main.cpp
//#include <iostream>
//#include <array>
//#include <string>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <gl/glew.h>
//#include <GLFW/glfw3.h>
//
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//
//#include "EclipseEngine/Shader.h"
//#include "EclipseEngine/VAO.h"
//#include "EclipseEngine/VBO.h"
//#include "EclipseEngine/EBO.h"
//#include "EclipseEngine/FrameBuffer.h"
//#include "EclipseEngine/Core.h"
//#include "EclipseEngine/Logger.h"
//#include "EclipseEngine/Component.h"
//#include "EclipseEngine/Texture.h"
//#include "EclipseEngine/Mesh.h"
//#include "EclipseEngine/Material.h"
//#include "EclipseEngine/Transform.h"
//#include "EclipseEngine/GameObject.h"
//#include "EclipseEngine/Grid.h"
//#include "PanelHandler.h"
//#include "AssetsPanel.h"
//#include "FPSpanel.h"
//#include "ConsolePanel.h"
//#include "ViewportPanel.h"
//#include "HierarchyPanel.h"
//
//using namespace std;
//
//using ivec2 = glm::ivec2;
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//#ifndef M_PI_2
//#define M_PI_2 1.57079632679489661923
//#endif
//
//static const ivec2 WINDOW_SIZE(1500, 844);
//
//#pragma region Primitives Vertex Data
//
//struct Cube
//{
//	std::vector<Vertex> vertices =
//	{ //               COORDINATES           /            NORMALS          /          COLOR           /      TEXTURE COORDINATES    //
//		Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},  // 0
//		Vertex{glm::vec3( 1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // 1
//		Vertex{glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},	 // 2
//		Vertex{glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},	 // 3
//		Vertex{glm::vec3( 1.0f, -1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},	 // 4
//		Vertex{glm::vec3( 1.0f,  1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},	 // 5
//		Vertex{glm::vec3(-1.0f,  1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},	 // 6
//		Vertex{glm::vec3(-1.0f, -1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}	 // 7
//	};
//	
//	std::vector<GLuint> indices =
//	{
//		0, 1, 2,
//		0, 2, 3,
//		1, 4, 5,
//		1, 5, 2,
//		4, 7, 6,
//		4, 6, 5,
//		7, 0, 3,
//		7, 3, 6,
//		0, 1, 4,
//		0, 4, 7,
//		3, 2, 5,
//		3, 5, 6
//	};
//
//	std::vector<Texture> catTexture
//	{
//		Texture("Assets/checkerboard.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
//	};
//};
//
//struct Sphere {
//	int latitude = 30;  // Number of latitude slices
//	int longitude = 30; // Number of longitude slices
//	float radius = 1.0f;
//
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//
//	Sphere() {
//		generateSphere();
//	}
//
//	float getR() const {
//		return radius;
//	}
//
//	void generateSphere() {
//		float const Lats = 1.0f / (float)(latitude - 1);
//		float const Longs = 1.0f / (float)(longitude - 1);
//
//		// Generate vertices
//		for (int r = 0; r < longitude; r++) {
//			for (int s = 0; s < latitude; s++) {
//				float const x = cos(2.0f * M_PI * s * Longs) * sin(M_PI * r * Lats);
//				float const y = sin(-M_PI_2 + M_PI * r * Lats);
//				float const z = sin(2.0f * M_PI * s * Longs) * sin(M_PI * r * Lats);
//
//				glm::vec3 position = glm::vec3(x * getR(), y * getR(), z * getR());
//				glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
//				glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
//				glm::vec2 texcoord = glm::vec2(s * Lats, r * Longs);
//
//				vertices.push_back({ position, normal, color, texcoord });
//			}
//		}
//
//		// Generate indices
//		for (int r = 0; r < longitude - 1; r++) {
//            for (int s = 0; s < latitude - 1; s++) {
//                indices.push_back(r * latitude + s);
//                indices.push_back((r + 1) * latitude + s);
//                indices.push_back(r * latitude + (s + 1)); // Correct CCW order for first triangle
//
//                indices.push_back(r * latitude + (s + 1));
//                indices.push_back((r + 1) * latitude + s);
//                indices.push_back((r + 1) * latitude + (s + 1)); // Correct CCW order for second triangle
//            }
//        }
//	}
//};
//
//#pragma endregion
//
//Core* core;
//
//int main(int argc, char** argv) {
//	core = new Core();
//	Logger::Init();
//
//	if (!core->Initialize()) {
//		std::cerr << "Engine initialization failed." << std::endl;
//		return -1;
//	}
//
//	PanelHandler panelHandler(core->window->GetWindow(), core->renderer->GetFramebuffer()); // editor side
//	ilInit();  // Initialize the DevIL library
//
//	Cube cubeData;
//	Sphere sphereData;
//
//	std::vector<Texture> houseTexture
//	{
//		Texture("Assets/Baker_house.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
//	};
//
//	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");
//	Shader gridShader("Shaders/grid.vert", "Shaders/grid.frag");
//
//	// Initialize the hierarchy panel
//	auto hierarchyPanel = std::dynamic_pointer_cast<HierarchyPanel>(panelHandler.GetPanel("Hierarchy Panel"));
//
//#pragma region Scene // This is the scene with game objects
//	auto cube = std::make_shared<GameObject>(); // This has to be in the engine side (SCENE)
//	cube.get()->name = "cube";
//	cube->AddComponent<Mesh>(sphereData.vertices, sphereData.indices, cubeData.catTexture);
//	cube->AddComponent<Material>(shaderProgram, cubeData.catTexture);
//	cube.get()->transform.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
//
//	auto house = std::make_shared<GameObject>(); // This has to be in the engine side (SCENE)
//	house.get()->name = "house";
//	std::string meshFilePath = "Assets/BakerHouse.FBX";
//	house->AddComponent<Mesh>(meshFilePath);
//	////auto& meshTexture = house.GetComponent<Mesh>()->GetTextures();    // It is supposed to get the defined texture from the fbx
//	house->AddComponent<Material>(shaderProgram, houseTexture);
//	house.get()->transform.SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
//#pragma endregion
//
//	hierarchyPanel->AddRootObject(cube); // Editor side (HIERARCY PANEL)
//	hierarchyPanel->AddRootObject(house); // Editor side (HIERARCY PANEL)
//
//	Camera camera(WINDOW_SIZE.x, WINDOW_SIZE.y, glm::vec3(7.0f, 4.0f, -7.0f)); // this specific camera is inside the editor
//	Grid grid(gridShader, camera); // This should be in the editor renderer
//
//	// Register the scroll callback for zoom control
//	glfwSetScrollCallback(core->window->GetWindow(), Camera::scroll_callback);
//
//	// Variables to track FPS and milliseconds per frame
//	float deltaTime = 0.0f;
//	float lastFrame = 0.0f;
//	//std::shared_ptr<Panel>* panelPtr = &panelHandler.GetPanel("FPS Panel");
//	auto panelPtr = std::dynamic_pointer_cast<FPSPanel>(panelHandler.GetPanel("FPS Panel"));
//
//	while (!core->window->ShouldClose()) // APP UPDATE LOOP
//	{
//		// fps
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		float fps = 1.0f / deltaTime;
//		float ms = deltaTime * 1000.0f;
//
//		core->PreUpdate();
//		camera.Inputs(core->window->GetWindow());
//		panelHandler.NewFrame(); // Editor side
//
//		camera.UpdateMatrix(0.1f, 100.0f);
//
//		core->Update(deltaTime);
//		cube->Draw(shaderProgram, camera);	// this should be in the update of the scene
//		house->Draw(shaderProgram, camera); // this should be in the update of the scene
//
//		grid.Draw(); // inside the editor renderer
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		// fps
//		if (panelPtr) {
//			if (auto fpsPanel = dynamic_cast<FPSPanel*>(panelPtr.get())) {
//				fpsPanel->Update(fps, ms);
//			}
//		}
//
//		// Rendering ImGui
//		panelHandler.Render();
//		panelHandler.EndFrame();
//
//		core->PostUpdate();
//	}
//
//	shaderProgram.Delete();
//	gridShader.Delete();
//	Logger::Close();
//	delete core;
//
//	return EXIT_SUCCESS;
//}
#pragma endregion
