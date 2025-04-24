#include "Character.h"
#include "Camera.h"
#include "Terrain.h"
#include <GL/glut.h>

// 全局对象
Terrain terrain;
Character character;
Camera camera;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    camera.SetupView(character);
    terrain.Draw();
    character.Draw();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'a': character.Move(-0.5, 0); character.rotation -= 5; break;
        case 'd': character.Move(0.5, 0); character.rotation += 5; break;
        case 'w': character.Move(0, -0.5); break;
        case 's': character.Move(0, 0.5); break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100); // 新增窗口起始位置
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = {50.0f, 100.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glutCreateWindow("Voxel World");
    
    // 新增视口重置回调
    glutReshapeFunc([](int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w/h, 0.1, 1000.0);
        glMatrixMode(GL_MODELVIEW);
    });
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);  // 启用材质颜色跟踪
    glShadeModel(GL_SMOOTH);       // 平滑着色模式
    terrain.Generate();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}