#include "Scene.h"
#include "Logger.h"

Scene::Scene()
{
}

Scene::~Scene()
{

}

bool Scene::Initialize()
{
	activeCamera = new Camera(1500, 844, glm::vec3(7.0f, 4.0f, -7.0f));
	auto initScene = modelLoader.LoadModel("Resources/Assets/fbx_files/Street/untitled.fbx");
	AddGameObject(initScene);
	return true;
}

bool Scene::Update(double dt)
{
	activeCamera->UpdateMatrix(0.1f, 100.0f);
    return true;
}

void Scene::Draw(Shader& shader)
{
	for (auto& obj : gameObjects)
	{
		glm::mat4 identity = obj->transform.GetMatrix();
		obj->Draw(shader, *activeCamera, identity);
	}
}

void Scene::AddGameObject(std::shared_ptr<GameObject> go)
{
	gameObjects.push_back(std::move(go));
}

void Scene::SetActiveCamera(Camera camera)
{
	activeCamera = &camera;
}

void Scene::AddCube()
{
	std::vector<Vertex> vertices =
	{ //               COORDINATES           /            NORMALS          /          COLOR           /      TEXTURE COORDINATES    //
		Vertex{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},  // 0
		Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},  // 1
		Vertex{glm::vec3(1.0f,  1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},	 // 2
		Vertex{glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},	 // 3
		Vertex{glm::vec3(1.0f, -1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},	 // 4
		Vertex{glm::vec3(1.0f,  1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},	 // 5
		Vertex{glm::vec3(-1.0f,  1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},	 // 6
		Vertex{glm::vec3(-1.0f, -1.0f,-1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}	 // 7
	};

	std::vector<GLuint> indices =
	{
		0, 1, 2,
		0, 2, 3,
		1, 4, 5,
		1, 5, 2,
		4, 7, 6,
		4, 6, 5,
		7, 0, 3,
		7, 3, 6,
		0, 4, 1,
		0, 7, 4,
		3, 2, 5,
		3, 5, 6
	};
	std::vector<Texture> catTexture
	{
		Texture("Resources/Assets/Textures/checkerboard.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	auto cube = std::make_shared<GameObject>(); // This has to be in the engine side (SCENE)
	cube.get()->name = "cube";
	cube->AddComponent<Mesh>(vertices, indices, catTexture);
	cube->AddComponent<Material>( catTexture);
	cube->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	auto cube2 = std::make_shared<GameObject>();
	cube2.get()->name = "cube2";
	cube2->AddComponent<Mesh>(vertices, indices, catTexture);
	cube2->AddComponent<Material>(catTexture);
	cube2->transform.position = glm::vec3(2.0f, 0.0f, 0.0f);

	auto cube3 = std::make_shared<GameObject>();
	cube3.get()->name = "cube2";
	cube3->AddComponent<Mesh>(vertices, indices, catTexture);
	cube3->AddComponent<Material>(catTexture);
	
	cube.get()->AddChild(cube2);
	//cube.get()->AddChild(cube3);
	AddGameObject(cube);
	Logger::Log("Cube added to the scene");
}