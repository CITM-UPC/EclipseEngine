#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <list>
#include "GameObject.h"
#include "Camera.h"
#include "ModelLoader.h"
#include "Skybox.h"

class Scene
{
public:
	Scene();
	~Scene();

	bool Initialize();
	bool Update(double dt);
	void Draw(Shader& shader);
	const std::list<std::shared_ptr<GameObject>>& GetObjects() const { return gameObjects; }
	Camera* GetActiveCamera() const { return activeCamera; }

	void AddGameObject(std::shared_ptr<GameObject> go);
	void AddEmptyGameObject();
	void SetActiveCamera(Camera* camera);
	void DeleteGameObject(const std::shared_ptr<GameObject>& go);

	void AddCube();

	std::unique_ptr<Skybox> skybox;
private:
	std::list<std::shared_ptr<GameObject >> gameObjects;
	Camera* activeCamera = nullptr;
	ModelLoader modelLoader;
};

#endif // SCENE_H