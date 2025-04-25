#pragma once
#include <glm/glm.hpp>

class Character;

class Camera {
public:
    float yaw = -90.0f;    // 水平旋转角
    float pitch = 0.0f;    // 垂直旋转角
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); // 视线方向

    void SetupView(const Character& character) const;
    void UpdateFrontVector();  // 新增方法声明
};