#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <string>
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"

class Core 
{
public:
    Core();
    ~Core();

    bool Initialize();

    bool PreUpdate();
	bool Update(double dt);
	bool PostUpdate();

	void CleanUp();

public:
    Renderer* renderer;
    Window* window;
	Scene* scene;
};

extern Core* core;

#endif // CORE_H