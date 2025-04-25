#include "InstancedRenderer.h"
#include "Cube.h"
#include <GL/glew.h>  // 包含GLEW头文件以访问OpenGL函数

// 构造函数实现
InstancedRenderer::InstancedRenderer() {
    glGenBuffers(1, &instanceVBO);
}

void InstancedRenderer::DrawInstanced(const Cube& cube, const std::vector<glm::mat4>& instances) {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::mat4), instances.data(), GL_STATIC_DRAW);
    cube.DrawInstanced(instances.size());
}