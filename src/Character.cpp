#include "Character.h"
#include <GL/gl.h>

void Character::Draw() const {
    glPushMatrix();
    glTranslatef(position[0], position[1]+1, position[2]);
    glRotatef(rotation, 0, 1, 0);
    
    glBegin(GL_TRIANGLES);
    // 金字塔绘制代码
    glEnd();
    
    glPopMatrix();
}

void Character::Move(float dx, float dz) {
    position[0] += dx;
    position[2] += dz;
}