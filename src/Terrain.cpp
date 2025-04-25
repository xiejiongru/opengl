#include "Terrain.h"
#include "InstancedRenderer.h"
#include "Cube.h"
#include <GL/gl.h>
#include <cmath>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
#include <iostream>

// Add constructor implementation
Terrain::Terrain() : initialized(false) {
    // Initialize heightMap to zero
    for (int z = 0; z < SIZE; z++) {
        for (int x = 0; x < SIZE; x++) {
            heightMap[x][z] = 0;
        }
    }
}

// Initialize OpenGL resources
void Terrain::Initialize() {
    if (!initialized) {
        terrainCube.Initialize();
        instancedRenderer.Initialize();
        initialized = true;
    }
}

bool Terrain::IsPositionValid(float x, float z) const {
    const float buffer = 0.3f; // 边界缓冲
    return (x >= buffer && x <= SIZE - 1 - buffer) && 
           (z >= buffer && z <= SIZE - 1 - buffer);
}

float Terrain::fractal_noise(float x, float z) {
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
    
    // Generate height map
    for(int z = 0; z < SIZE; z++) {
        for(int x = 0; x < SIZE; x++) {
            float noise = fractal_noise(x*0.1f, z*0.1f);
            heightMap[x][z] = static_cast<int>(abs(noise)*4) + 2;
        }
    }
        // 增加平滑滤波
        for(int z = 1; z < SIZE-1; z++){
            for(int x = 1; x < SIZE-1; x++){
                heightMap[x][z] = (heightMap[x-1][z] + heightMap[x+1][z] 
                                + heightMap[x][z-1] + heightMap[x][z+1]) / 4;
            }
        }
    // Generate instance matrices
    GenerateInstanceMatrices();
}

void Terrain::Draw() const {
    // Use fixed-function pipeline for now
    glPushMatrix();
    
    // Only draw some cubes for better performance during testing
    for (int z = 0; z < SIZE; z ++) {
        for (int x = 0; x < SIZE; x ++) {
            int height = heightMap[x][z];
            for (int y = 0; y < height; y++) {
                glPushMatrix();
                glTranslatef(x, y, z);
                
                // Draw a simple colored cube
                glBegin(GL_QUADS);
                // Front face (red)
                glColor3f(0.8f, 0.2f, 0.1f);
                glVertex3f(-0.5f, -0.5f, 0.5f);
                glVertex3f(0.5f, -0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(-0.5f, 0.5f, 0.5f);
                
                // Back face (blue)
                glColor3f(0.1f, 0.1f, 0.9f);
                glVertex3f(-0.5f, -0.5f, -0.5f);
                glVertex3f(-0.5f, 0.5f, -0.5f);
                glVertex3f(0.5f, 0.5f, -0.5f);
                glVertex3f(0.5f, -0.5f, -0.5f);
                
                // Top face (yellow)
                glColor3f(0.9f, 0.9f, 0.1f);
                glVertex3f(-0.5f, 0.5f, -0.5f);
                glVertex3f(-0.5f, 0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(0.5f, 0.5f, -0.5f);
                glEnd();
                
                glPopMatrix();
            }
        }
    }
    
    // Draw coordinate axes
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0); glVertex3f(10,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0); glVertex3f(0,10,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0); glVertex3f(0,0,10);
    glEnd();
    
    glPopMatrix();
}

int Terrain::GetHeight(float x, float z) const {
    int ix = static_cast<int>(x);
    int iz = static_cast<int>(z);
    if (ix >= 0 && ix < SIZE && iz >= 0 && iz < SIZE) {
        return heightMap[ix][iz];
    }
    return 0;
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