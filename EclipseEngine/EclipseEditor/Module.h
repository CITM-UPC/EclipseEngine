#ifndef MODULE_H
#define MODULE_H

#include <string>

class App;

class Module
{
public:
	Module() {}
	Module(const char* name, App* app) : name(name), app(app) {}
	virtual ~Module() {}

	virtual bool Initialize() { return true; }
	virtual bool CleanUp() { return true; }

	virtual bool PreUpdate() { return true; }
	virtual bool Update(double dt) { return true; }
	virtual bool PostUpdate() { return true; }

	void Enable() { active = true; }
	void Disable() { active = false; }

public:
	std::string name;
	bool active = true;
	App* app = nullptr;
};

#endif //MODULE_H