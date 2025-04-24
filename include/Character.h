#pragma once
#include <GL/gl.h>

class Character {
public:
    float position[3] = {25, 0, 25};
    float rotation = 0.0f;
    
    void Draw() const;
    void Move(float dx, float dz);
};