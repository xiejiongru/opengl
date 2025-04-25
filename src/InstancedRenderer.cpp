#include "InstancedRenderer.h"
#include "Cube.h"
#include <GL/glew.h>
#include <iostream>

// Default constructor - doesn't use OpenGL
InstancedRenderer::InstancedRenderer() : instanceVBO(0), initialized(false) {
    // Don't call any OpenGL functions here
}

// Initialize OpenGL resources when ready
void InstancedRenderer::Initialize() {
    if (!initialized) {
        glGenBuffers(1, &instanceVBO);
        initialized = true;
    }
}

InstancedRenderer::~InstancedRenderer() {
    if (initialized && instanceVBO != 0) {
        glDeleteBuffers(1, &instanceVBO);
        instanceVBO = 0;
    }
}

void InstancedRenderer::DrawInstanced(const Cube& cube, const std::vector<glm::mat4>& instances) const {
    if (!initialized) {
        std::cerr << "InstancedRenderer not initialized" << std::endl;
        return;
    }
    
    if (instances.empty()) {
        return;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::mat4), 
                instances.data(), GL_STATIC_DRAW);
    
    // Simple draw elements for now
    GLuint cubeVAO = cube.GetVAO();
    if (cubeVAO != 0) {
        glBindVertexArray(cubeVAO);
        // 配置矩阵属性指针（每列一个属性）
        for (int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(1 + i);
            glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, 
                sizeof(glm::mat4), (void*)(i * sizeof(glm::vec4)));
            glVertexAttribDivisor(1 + i, 1); // 重要：设置实例化属性
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}