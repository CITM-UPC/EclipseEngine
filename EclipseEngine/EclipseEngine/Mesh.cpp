#include "Mesh.h"
#include "Logger.h"

Mesh::Mesh(std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices, std::vector<Texture>& _textures) 
					: vertices(_vertices),				indices(_indices),			   textures(_textures) 
{
	VAO.Bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	for (const auto& vertex : vertices) localAABB.Expand(vertex.position);
	
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Update() 
{
	// Empty Update method
}

void Mesh::Draw(Shader& shader, Camera& camera) // Camera should not be passed only the position (vec3)
{
	VAO.Bind();

	//glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix"); // This should be moved to the renderer

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i].Unbind();
	}

	VAO.Unbind();
}

AABB Mesh::GetWorldAABB(const glm::mat4& transform) const {
	AABB worldAABB = localAABB;
	worldAABB.Transform(transform);
	return worldAABB;
}