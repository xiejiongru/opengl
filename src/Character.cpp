#include "Character.h"
#include "Terrain.h"
#include <GL/gl.h>
#include <iostream>

void Character::Draw() const {
    glPushMatrix();
    glTranslatef(position[0], position[1]+1, position[2]);
    glRotatef(rotation, 0, 1, 0);
    glScalef(0.8f, 0.2f, 0.8f); // 扁平化
    
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

    // 简单八面体示例
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 1, 0); // 顶点
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();

    // 添加方向线
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex3f(0, 1.5f, 0);
    glVertex3f(0, 1.5f, -2.0f); // 白线指示面朝方向
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1,0,0); // 红色右方向
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glColor3f(0,1,0); // 绿色前方向 
    glVertex3f(0,1,0); glVertex3f(0,1,-2);
    glEnd();
}

void Character::Move(float lateral, float forward, const Terrain& terrain) {
    float radians = glm::radians(rotation);
    
    // 计算移动方向向量
    glm::vec3 moveDir(
        lateral * cos(radians) + forward * sin(radians),
        0,
        lateral * sin(radians) - forward * cos(radians)
    );

    float newX = position[0] + moveDir.x;
    float newZ = position[2] + moveDir.z;
    
    if (!terrain.IsPositionValid(newX, newZ)) {
        std::cout << "Collision at: " << newX << "," << newZ << std::endl;
        return; // 仅阻止移动，不重置位置
    }

    if (!terrain.IsPositionValid(newX, newZ)) {
        // 处理越界情况（如回退/边界限制）
        position[0] = position[2] = 25.0f;
        position[1] = terrain.GetHeight(25.0f, 25.0f) + 1.0f;
    }

    // 更新位置
    position[0] = newX;
    position[2] = newZ;
    position[1] = terrain.GetHeight(newX, newZ) + 1.0f;  // 移除越界重置逻辑

}