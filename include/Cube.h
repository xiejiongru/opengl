#pragma once
#include <GL/glew.h> 
#include <glm/glm.hpp>

class Cube {
public:
    Cube();  
    ~Cube(); 
    void DrawInstanced(int instanceCount) const;

private:
    GLuint vao;  // 顶点数组对象
    GLuint vbo;  // 顶点缓冲区
    GLuint ebo;  // 元素缓冲区
};