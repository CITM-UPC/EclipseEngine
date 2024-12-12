#ifndef GRID_H
#define GRID_H

#include "EclipseEngine/VAO.h"
#include "EclipseEngine/EBO.h"
#include "EclipseEngine/Shader.h"
#include "EclipseEngine/Camera.h"

class Grid
{
public:
	Grid();

	void Draw(Camera* camera);

private:
	std::vector<Vertex> gridVertices;
	Shader* shader;
	VAO vao;

	const float gridSize = 50.0f; // Size of the grid
	const int gridLines = 30;      // Number of lines in each direction
	const float lineSpacing = gridSize / gridLines;
};

#endif // GRID_H