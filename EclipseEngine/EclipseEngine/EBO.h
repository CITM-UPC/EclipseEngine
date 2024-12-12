#ifndef EBO_H
#define EBO_H

#include <vector>
#include <GL/glew.h>

class EBO
{
public:
	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
};

#endif //EBO_H
