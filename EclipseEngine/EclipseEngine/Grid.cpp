//#include "Grid.h"
//
//Grid::Grid(Shader& _shader, Camera& _camera) : shader(_shader), camera(_camera)
//{
//
//	for (int i = -gridLines / 2; i <= gridLines / 2; ++i) 
//	{
//		float offset = i * lineSpacing;
//
//		glm::vec3 neutralColor = glm::vec3(0.3f, 0.3f, 0.3f);
//
//		// Horizontal line (Z-axis)
//		glm::vec3 colorZ = (offset == 0.0f) ? glm::vec3(0.0f, 0.75f, 0.0f) : neutralColor;
//		gridVertices.push_back({ glm::vec3(-gridSize / 2, 0.0f, offset), glm::vec3(0.0f),colorZ, glm::vec2(0.0f) });
//		gridVertices.push_back({ glm::vec3(gridSize / 2, 0.0f, offset), glm::vec3(0.0f), colorZ, glm::vec2(1.0f) });
//
//		// Vertical line (X-axis)
//		glm::vec3 colorX = (offset == 0.0f) ? glm::vec3(0.75f, 0.0f, 0.0f) : neutralColor; // Red for center X-axis
//		gridVertices.push_back({ glm::vec3(offset, 0.0f, -gridSize / 2), glm::vec3(0.0f),colorX, glm::vec2(0.0f) });
//		gridVertices.push_back({ glm::vec3(offset, 0.0f, gridSize / 2), glm::vec3(0.0f),colorX, glm::vec2(1.0f) });
//	}
//	// Step 2: Create VAO and VBO for the grid if they don't exist
//	vao.Bind(); // Bind the VAO
//	VBO gridVBO(gridVertices); // Initialize VBO with grid vertices
//
//	vao.LinkAttrib(gridVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position)); // Link position
//	vao.LinkAttrib(gridVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));    // Link color
//	vao.Unbind(); // Unbind the VAO
//	gridVBO.Unbind();
//}
//
//void Grid::Draw()
//{
//	// Draw the grid
//	shader.Activate();
//	vao.Bind();
//	glLineWidth(1.0f); // Set line width
//
//	glm::mat4 model = glm::mat4(1.0f); // Identity matrix for the grid
//	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
//	glm::vec3 whiteColor(0.3f, 0.3f, 0.3f);
//	glUniform3fv(glGetUniformLocation(shader.ID, "gridColor"), 1, glm::value_ptr(whiteColor));
//	// Pass camera matrices
//	camera.Matrix(shader, "camMatrix");
//
//	glDrawArrays(GL_LINES, 0, gridVertices.size());
//	vao.Unbind();
//}