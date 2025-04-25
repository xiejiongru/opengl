#include "Camera.h"
#include "Character.h"
#include <GL/glu.h>
#include <cmath>
#include <glm/glm.hpp>

// 原 SetupView 实现保持不变
void Camera::SetupView(const Character& character) const {
    const float camDistance = 15.0f;
    const float lookAhead = 5.0f;
    const float radians = glm::radians(character.rotation);
    
    gluLookAt(
        character.position[0] - camDistance * sin(radians),
        character.position[1] + 15.0f,
        character.position[2] - camDistance * cos(radians),
        character.position[0] - lookAhead, 
        character.position[1] + 5.0f,
        character.position[2] - lookAhead,
        0, 1, 0
    );
}

// 新增 UpdateFrontVector 实现
void Camera::UpdateFrontVector() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}