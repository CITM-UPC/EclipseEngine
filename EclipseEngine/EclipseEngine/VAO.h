#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include "VBO.h"

class VAO
{
public:
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
};
#endif //VAO_H