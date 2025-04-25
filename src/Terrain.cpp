#include "Terrain.h"
#include "InstancedRenderer.h"
#include "Cube.h"           
#include <GL/gl.h>
#include <cmath>
#include <ctime>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>  
#include <GL/glut.h>

float Terrain::fractal_noise(float x, float z) {  // 作为成员函数实现
    float total = 0;
    float freq = 1.0, amp = 0.5;
    for(int i=0; i<4; i++) {
        total += amp * sin(x*freq) * cos(z*freq*0.7);
        freq *= 2.0;
        amp *= 0.5;
    }
    return total;
}

void Terrain::Generate() {
    srand(time(0));
    for(int z = 0; z < SIZE; z++) {
        for(int x = 0; x < SIZE; x++) {
            float noise = fractal_noise(x*0.1f, z*0.1f);  // 使用成员函数
            heightMap[x][z] = static_cast<int>(abs(noise)*4) + 2;
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
    const GLfloat colors[][3] = 
    {
        {0.8f, 0.2f, 0.1f},  // 红
        {0.1f, 0.1f, 0.9f},  // 蓝 
        {0.9f, 0.6f, 0.1f}   // 黄
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

    // 绘制坐标轴
    glBegin(GL_LINES);
    glColor3f(1,0,0); // X轴红色
    glVertex3f(0,0,0); glVertex3f(10,0,0);
    glColor3f(0,1,0); // Y轴绿色
    glVertex3f(0,0,0); glVertex3f(0,10,0);
    glColor3f(0,0,1); // Z轴蓝色
    glVertex3f(0,0,0); glVertex3f(0,0,10);
    glEnd();
    
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

int Terrain::GetHeight(float x, float z) const {
    int ix = static_cast<int>(x);
    int iz = static_cast<int>(z);
    if (ix >= 0 && ix < SIZE && iz >= 0 && iz < SIZE) {
        return heightMap[ix][iz];
    }
    return 0; // 越界返回0
}

void Terrain::GenerateInstanceMatrices() {
    cubeInstances.clear();
    for (int z = 0; z < SIZE; z++) {
        for (int x = 0; x < SIZE; x++) {
            int height = heightMap[x][z];
            for (int y = 0; y < height; y++) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
                cubeInstances.push_back(model);
            }
        }
    }
}

