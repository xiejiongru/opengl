#include "Character.h"
#include "Terrain.h"
#include <GL/gl.h>

void Character::Draw() const {
    glPushMatrix();
    glTranslatef(position[0], position[1]+1, position[2]);
    glRotatef(rotation, 0, 1, 0);
    
    glBegin(GL_TRIANGLES);
    // 底面（四边形分解为两个三角形）
    glColor3f(0.8, 0.2, 0.1);
    glVertex3f(0, 0, 0.5); glVertex3f(-0.5, 0, -0.5); glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0, -0.5); glVertex3f(-0.5, 0, -0.5); glVertex3f(0, 0, 0.5);

    // 侧面三角形
    glColor3f(0.1, 0.8, 0.1);
    glVertex3f(0, 1, 0); glVertex3f(-0.5, 0, -0.5); glVertex3f(0.5, 0, -0.5);
    glVertex3f(0, 1, 0); glVertex3f(0.5, 0, -0.5); glVertex3f(0, 0, 0.5);
    glVertex3f(0, 1, 0); glVertex3f(0, 0, 0.5); glVertex3f(-0.5, 0, -0.5);
    glEnd();
    
    glPopMatrix();
}

void Character::Move(float dx, float dz, const Terrain& terrain) {  // 接受地形参数
    position[0] += dx;
    position[2] += dz;
    position[1] = terrain.GetHeight(position[0], position[2]) + 1.0f;  // 通过实例调用
}