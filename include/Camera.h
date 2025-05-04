#pragma once
#include <glm/glm.hpp>

class Character;

class Camera {
public:
    float yaw = -90.0f;    // Horizontal rotation angle
    float pitch = 0.0f;    // Vertical rotation angle
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); // View direction

    void SetupView(const Character& character) const;
    void UpdateFrontVector();  // New method declaration
};