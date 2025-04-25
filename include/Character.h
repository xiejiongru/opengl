#pragma once
#include "Terrain.h" 

class Terrain;  // 前向声明

class Character {
public:
    float position[3] = {25, 0, 25};
    float rotation = 0.0f;
    
    void Draw() const;
    void Move(float dx, float dz, const Terrain& terrain);  // 传入地形引用
};