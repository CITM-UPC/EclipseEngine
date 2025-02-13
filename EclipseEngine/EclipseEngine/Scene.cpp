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
	//activeCamera = new Camera(1500, 844, glm::vec3(7.0f, 4.0f, -7.0f));
	auto cameraGO = std::make_shared<GameObject>();
	cameraGO->name = "Main Camera";
	cameraGO->AddComponent<Camera>(1500, 844, glm::vec3(7.0f, 4.0f, -7.0f));
	SetActiveCamera(cameraGO->GetComponent<Camera>());
	activeCamera->SetNearPlane(5.0f);
	activeCamera->SetFarPlane(100.0f);
	AddGameObject(cameraGO);
	//auto initScene = modelLoader.LoadModel("Resources/Assets/fbx_files/Street/untitled.fbx");
	//AddGameObject(initScene);

	std::vector<std::string> cubemapFaces = {
	"Resources/skybox/skybox1/right.png", "Resources/skybox/skybox1/left.png", "Resources/skybox/skybox1/top.png",
	"Resources/skybox/skybox1/bottom.png", "Resources/skybox/skybox1/front.png", "Resources/skybox/skybox1/back.png"
	};

	//std::vector<std::string> cubemapFaces = {
	//"Resources/skybox/skycube_1/right.bmp", "Resources/skybox/skycube_1/left.bmp", "Resources/skybox/skycube_1/top.bmp",
	//"Resources/skybox/skycube_1/bottom.bmp", "Resources/skybox/skycube_1/front.bmp", "Resources/skybox/skycube_1/back.bmp"
	//};

	skybox = std::make_unique<Skybox>(cubemapFaces);

	return true;
}

bool Scene::Update(double dt)
{
	if (activeCamera)
	{
		activeCamera->UpdateMatrix(activeCamera->nearPlane, activeCamera->farPlane);
	}
	for (auto& obj : gameObjects)
	{
		obj->Update();
	}
    return true;
}

void Scene::Draw(Shader& shader)
{
	skybox->Draw(*activeCamera);
	for (auto& obj : gameObjects){
		obj->Draw(shader, *activeCamera, obj->transform.GetMatrix());
	}
}

void Scene::AddGameObject(std::shared_ptr<GameObject> go)
{
	gameObjects.push_back(std::move(go));
}

void Scene::AddEmptyGameObject()
{
	auto emptyGameObject = std::make_shared<GameObject>();
	emptyGameObject->name = "Empty GameObject";
	gameObjects.push_back(emptyGameObject);
}


void Scene::SetActiveCamera(Camera* camera)
{
	if (activeCamera != camera) 
		activeCamera = camera;
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
		Texture("Resources/Assets/Textures/default.png","diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	auto cube = std::make_shared<GameObject>(); // This has to be in the engine side (SCENE)
	cube.get()->name = "cube";
	cube->AddComponent<Mesh>(vertices, indices, catTexture);
	cube->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	AddGameObject(cube);
	Logger::Log("Cube added to the scene");
}

void Scene::DeleteGameObject(const std::shared_ptr<GameObject>& go)
{
	go->DeleteAllComponents();
	go->DeleteAllChildren();
	gameObjects.remove(go);
}