#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <list>
#include "GameObject.h"
#include "Camera.h"

class Scene
{
public:
	Scene();
	~Scene();

	bool Initialize();
	bool Update(double dt);
	void Draw();
	const std::list<std::shared_ptr<GameObject>>& GetObjects() const { return gameObjects; }
	Camera* GetActiveCamera() const { return activeCamera; }

	void AddGameObject(std::shared_ptr<GameObject> go);
	void SetActiveCamera(Camera camera);

	void AddCube();

private:
	std::list<std::shared_ptr<GameObject >> gameObjects;
	Camera* activeCamera = nullptr;
};

#endif // SCENE_H