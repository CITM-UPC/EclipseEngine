#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include <memory>
#include <GL/glew.h>
#include <IL/il.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Camera.h"

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    void Draw(const Camera& camera);

private:
    GLuint skyboxVAO, skyboxVBO;
    GLuint cubemapTexture;
    std::unique_ptr<Shader> skyboxShader;

    GLuint LoadCubemap(const std::vector<std::string>& faces);
};

#endif // SKYBOX_H
