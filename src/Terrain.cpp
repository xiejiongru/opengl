#include "Terrain.h"
#include <GL/gl.h>
#include <cmath>
#include <ctime>
#include <glm/glm.hpp> 
#include <GL/glut.h>

void Terrain::Generate() {
    srand(time(0));
    for(int z = 0; z < SIZE; z++) {
        for(int x = 0; x < SIZE; x++) {
            // 使用简单三角函数生成地形
            float noise = 0.5f * sin(x*0.5f) + 0.5f * cos(z*0.3f);
            heightMap[x][z] = static_cast<int>((noise + 1) * 3) + 2;
        }
    }
}

void DrawCube() {
    const GLfloat vertices[][3] = {
        // 只保留8个顶点
        {-0.5,-0.5,-0.5}, // 0
        {0.5,-0.5,-0.5},  // 1
        {0.5,0.5,-0.5},   // 2
        {-0.5,0.5,-0.5},  // 3
        {-0.5,-0.5,0.5},  // 4
        {0.5,-0.5,0.5},   // 5
        {0.5,0.5,0.5},    // 6
        {-0.5,0.5,0.5}    // 7
    };
    
    const int faces[6][4] = {{0,1,2,3}, {5,4,7,6}, {4,0,3,7},
                            {1,5,6,2}, {4,5,1,0}, {3,2,6,7}};
    
    // 随机生成三原色组合
    const GLfloat colors[][3] = {
        {0.9f, 0.1f, 0.1f},  // 红
        {0.1f, 0.1f, 0.9f},  // 蓝 
        {0.9f, 0.9f, 0.1f}   // 黄
    };
    
    // 按高度选择颜色
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    int colorIndex = static_cast<int>(std::abs(std::sin(time)) * 3) % 3;

    glBegin(GL_QUADS);
    for(int i=0; i<6; ++i) {
        glColor3fv(colors[i]);
        for(int j=0; j<4; ++j)
            glVertex3fv(vertices[faces[i][j]]);
    }
    glEnd();
}
void Terrain::Draw() const {
    for(int z = 0; z < SIZE; z++) {
        for(int x = 0; x < SIZE; x++) {
            int height = heightMap[x][z];
            for(int y = 0; y < height; y++) {
                glPushMatrix();
                glTranslatef(x, y, z);
                DrawCube();
                glPopMatrix();
            }
        }
    }
}
