#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "Component.h"

class Material : public Component 
{
public:
    Material(const std::vector<Texture>& textures);

    void BindTextures(Shader& shader);
    void Update() override;

public:
    std::vector<Texture> textures;

};

#endif // MATERIAL_H