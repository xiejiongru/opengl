#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Cube.h"  

class InstancedRenderer {
public:
    unsigned int instanceVBO;

    InstancedRenderer();  
    ~InstancedRenderer(); 

    void DrawInstanced(const Cube& cube, const std::vector<glm::mat4>& instances);
};