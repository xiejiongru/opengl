#include "Camera.h"
#include "Character.h"

#include <GL/glu.h>
#include <cmath>
#include <glm/glm.hpp>

void Camera::SetupView(const Character& character) const {
    // 45度俯视视角
    const float cameraHeight = 30.0f;
    const float lookAhead = 10.0f;

    gluLookAt(
        character.position[0] - lookAhead, 
        character.position[1] + cameraHeight,
        character.position[2] - lookAhead,
        character.position[0] + lookAhead/2,  // 视角焦点前移
        character.position[1],
        character.position[2] + lookAhead/2,
        0, 1, 0
    );
}