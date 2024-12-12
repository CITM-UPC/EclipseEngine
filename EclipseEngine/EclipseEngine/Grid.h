#ifndef GRID_H
#define GRID_H

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Camera.h"

class Grid
{
public:
	Grid(Shader& shader, Camera& camera);

	void Draw();

public:
	std::vector<Vertex> gridVertices;
	Shader& shader;
	Camera& camera;
	VAO vao;

	const float gridSize = 50.0f; // Size of the grid
	const int gridLines = 30;      // Number of lines in each direction
	const float lineSpacing = gridSize / gridLines;
};

#endif // GRID_H