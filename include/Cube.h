#pragma once
#include <GL/glew.h>

class Cube {
public:
    Cube();
    ~Cube();
    
    // Add initialization method
    void Initialize();
    GLuint GetVAO() const { return vao; }
    void DrawInstanced(int instanceCount) const;

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    bool initialized;
};