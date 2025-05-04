#include "Character.h"
#include "Terrain.h"
#include <GL/gl.h>
#include <iostream>

void Character::Draw() const {
    glPushMatrix();
    glTranslatef(position[0], position[1]+1, position[2]);
    glRotatef(rotation, 0, 1, 0);
    glScalef(0.8f, 0.2f, 0.8f); // Flatten
    
    glBegin(GL_TRIANGLES);
    // Bottom face (quadrilateral decomposed into two triangles)
    glColor3f(0.8, 0.2, 0.1);
    glVertex3f(0, 0, 0.5); 
    glVertex3f(-0.5, 0, -0.5); 
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(0.5, 0, -0.5); 
    glVertex3f(-0.5, 0, -0.5); 
    glVertex3f(0, 0, 0.5);

    // Side triangles
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

    // Simple octahedron example
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 1, 0); // Vertex
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(0.5, 0, -0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(-0.5, 0, 0.5);
    glEnd();

    // Add direction lines
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex3f(0, 1.5f, 0);
    glVertex3f(0, 1.5f, -2.0f); // White line indicates facing direction
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1,0,0); // Red right direction
    glVertex3f(0,1,0); glVertex3f(1,1,0);
    glColor3f(0,1,0); // Green forward direction 
    glVertex3f(0,1,0); glVertex3f(0,1,-2);
    glEnd();
}

void Character::Move(float lateral, float forward, const Terrain& terrain) {
    float radians = glm::radians(rotation);
    
    // Calculate movement direction vector
    glm::vec3 moveDir(
        lateral * cos(radians) + forward * sin(radians),
        0,
        lateral * sin(radians) - forward * cos(radians)
    );

    float newX = position[0] + moveDir.x;
    float newZ = position[2] + moveDir.z;
    
    if (!terrain.IsPositionValid(newX, newZ)) {
        std::cout << "Collision at: " << newX << "," << newZ << std::endl;
        return; // Only prevent movement, do not reset position
    }

    if (!terrain.IsPositionValid(newX, newZ)) {
        // Handle out-of-bounds case (e.g., backtrack/boundary restriction)
        position[0] = position[2] = 25.0f;
        position[1] = terrain.GetHeight(25.0f, 25.0f) + 1.0f;
    }

    // Update position
    position[0] = newX;
    position[2] = newZ;
    position[1] = terrain.GetHeight(newX, newZ) + 1.0f;  // Remove out-of-bounds reset logic

}