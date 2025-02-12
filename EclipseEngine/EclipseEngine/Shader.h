#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 

std::string get_file_contents(const char* filename);

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentShader);

	void Activate();
	void Delete();

	void SetMat4(const std::string& name, const glm::mat4& matrix) const { glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); }
	void SetFloat(const std::string& name, float value) { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
	void SetFloat4(const std::string& name, float v0, float v1, float v2, float v3) { glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3); }
	void SetInt(const std::string& name, int value) { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
	void SetVec3(const std::string& name, const glm::vec3& value) { glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); }

	GLuint ID;
};

#endif //SHADER_H
