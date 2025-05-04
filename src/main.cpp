#include <iostream>
#include "Character.h"
#include "Camera.h"
#include "Terrain.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

// Global objects
Camera camera;
Character character;
Terrain terrain;
int frameCount = 0;
int lastFpsTime = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    camera.SetupView(character);
    terrain.Draw();
    character.Draw();
    
    glutSwapBuffers();

    // FPS calculation
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    frameCount++;
    
    if (currentTime - lastFpsTime >= 1000) { // Update every second
        float fps = frameCount * 1000.0f / (currentTime - lastFpsTime);
        char title[128];
        snprintf(title, sizeof(title), "Voxel World - FPS: %.1f", fps);
        glutSetWindowTitle(title);
        lastFpsTime = currentTime;
        frameCount = 0;
    }
}

void keyboard(unsigned char key, int, int) {
    const float moveSpeed = 0.5f;
    const float rotateSpeed = 5.0f;
    
    switch(key) {
        case 'q': // Turn left
            character.rotation += rotateSpeed;
            break;
        case 'e': // Turn right
            character.rotation -= rotateSpeed;
            break;
        case 'a': // Move left
            character.Move(-moveSpeed, 0, terrain); 
            break;
        case 'd': // Move right
            character.Move(moveSpeed, 0, terrain);
            break;
        case 'w': // Move forward
            character.Move(0, moveSpeed, terrain);
            break;
        case 's': // Move backward
            character.Move(0, -moveSpeed, terrain);
            break;
    }
    glutPostRedisplay();
}
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    std::cout << "GLEW initialized successfully" << std::endl;
    
    // Now that GLEW is initialized, initialize our objects
    terrain.Initialize();
    
    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    // Lighting setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 50.0f, 100.0f, 50.0f, 0.0f };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    
    // Generate terrain and place character
    terrain.Generate();
    character.position[1] = terrain.GetHeight(character.position[0], character.position[2]) + 1.0f;
}

int main(int argc, char** argv) {
    std::cout << "Starting Voxel World..." << std::endl;
    
    // Initialize GLUT first
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Voxel World");
    
    // Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    // Initialize OpenGL and our objects after GLUT is ready
    init();
    
    // Enter main loop
    std::cout << "Entering main loop" << std::endl;
    glutMainLoop();
    
    return 0;
}