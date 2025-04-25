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
    glVertex3f(0, 0, 0.5); 
    glVertex3f(-0.5, 0, -0.5); 
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0, -0.5); 
    glVertex3f(-0.5, 0, -0.5); 
    glVertex3f(0, 0, 0.5);

    // 侧面三角形
    glColor3f(0.1, 0.8, 0.1);
    glVertex3f(0, 1, 0); 
    glVertex3f(-0.5, 0, -0.5); 
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0, 1, 0); 
    glVertex3f(0.5, 0, -0.5); 
    glVertex3f(0, 0, 0.5);
    glVertex3f(0, 1, 0); 
    glVertex3f(0, 0, 0.5); 
    glVertex3f(-0.5, 0, -0.5);
    glEnd();
    
    glPopMatrix();
}

void Character::Move(float dx, float dz, const Terrain& terrain) {
    float newX = position[0] + dx;
    float newZ = position[2] + dz;

    // 边界检查
    if (newX < 0 || newX >= Terrain::SIZE) return;
    if (newZ < 0 || newZ >= Terrain::SIZE) return;

    // 更新位置
    position[0] = newX;
    position[2] = newZ;
    position[1] = terrain.GetHeight(newX, newZ) + 1.0f;
}