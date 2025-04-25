#include "Cube.h"
#include <GL/glew.h>
#include <iostream>

// Default constructor - doesn't use OpenGL
Cube::Cube() : vao(0), vbo(0), ebo(0), initialized(false) {
    // Don't call any OpenGL functions here
}

// Initialize OpenGL resources when ready
void Cube::Initialize() {
    if (initialized) return;
    
    // Create buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);
    
    // Simple cube vertices (positions only)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };
    
    // Simple cube indices
    unsigned int indices[] = {
        0, 1, 3, 3, 1, 2,  // front
        1, 5, 2, 2, 5, 6,  // right
        5, 4, 6, 6, 4, 7,  // back
        4, 0, 7, 7, 0, 3,  // left
        3, 2, 7, 7, 2, 6,  // top
        4, 5, 0, 0, 5, 1   // bottom
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    initialized = true;
}

Cube::~Cube() {
    if (initialized) {
        if (ebo != 0) glDeleteBuffers(1, &ebo);
        if (vbo != 0) glDeleteBuffers(1, &vbo);
        if (vao != 0) glDeleteVertexArrays(1, &vao);
    }
}

void Cube::DrawInstanced(int instanceCount) const {
    if (!initialized || vao == 0) {
        return;
    }
    
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, instanceCount);
    glBindVertexArray(0);
}