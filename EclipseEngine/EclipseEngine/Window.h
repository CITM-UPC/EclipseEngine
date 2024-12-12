#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.h"

class Window
{
public:
	Window(int width, int height, const std::string& title, const std::string& iconPath = "");
	~Window();

	bool Initialize();
	bool ShouldClose() const;
	void CleanUp();

	GLFWwindow* GetWindow() const { return m_Window; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

private:
	bool InitializeGLFW();
	bool InitializeOpenGL();

private:
	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;
	int m_Width, m_Height;
	std::string m_Title;
	Texture* m_IconTexture;
	std::string m_IconPath;
};

#endif // WINDOW_H