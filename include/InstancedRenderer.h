#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Cube.h"

class InstancedRenderer {
public:
    unsigned int instanceVBO;
    bool initialized;

    InstancedRenderer();
    ~InstancedRenderer();
    
    // Add initialization method to call after OpenGL is ready
    void Initialize();
    void DrawInstanced(const Cube& cube, const std::vector<glm::mat4>& instances) const;
};