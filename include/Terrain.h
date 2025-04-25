#pragma once
#include <vector>       
#include <glm/glm.hpp>  

class Terrain {
public:
    static const int SIZE = 50;
    float heightMap[SIZE][SIZE];
    std::vector<glm::mat4> cubeInstances;  // 新增实例矩阵容器

    void Generate();
    void Draw() const;
    int GetHeight(float x, float z) const;          // 声明GetHeight
    void GenerateInstanceMatrices();                // 声明GenerateInstanceMatrices

private:
    float fractal_noise(float x, float z);
};