#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "InstancedRenderer.h"
#include "Cube.h"

class Terrain {
public:
    static const int SIZE = 50;
    float heightMap[SIZE][SIZE];
    std::vector<glm::mat4> cubeInstances;

    InstancedRenderer instancedRenderer;
    Cube terrainCube;

    Terrain();  // Add constructor declaration
    void Initialize();  // Add initialization method
    void Generate();
    void Draw() const;
    int GetHeight(float x, float z) const;
    void GenerateInstanceMatrices();
    
private:
    float fractal_noise(float x, float z);
    bool initialized;
};