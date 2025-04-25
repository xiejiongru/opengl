#include <iostream>
#include "Character.h"
#include "Camera.h"
#include "Terrain.h"
#define GLEW_NO_GLU      
#define GLEW_STATIC  
#include <GL/glew.h>
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
        case 'a': 
            character.Move(-0.5, 0, terrain);  // 传递地形引用
            character.rotation -= 5; 
            break;
        case 'd': 
            character.Move(0.5, 0, terrain);
            character.rotation += 5; 
            break;
        case 'w': 
            character.Move(0, -0.5, terrain); 
            break;
        case 's': 
            character.Move(0, 0.5, terrain); 
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100); // 新增窗口起始位置

    // 改为手动控制光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 50.0, 100.0, 50.0, 0.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutCreateWindow("Voxel World");
    
    // 初始化GLEW（必须在OpenGL上下文创建后）
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW初始化失败: " << glewGetErrorString(err) << std::endl;
        return 1;
    }

    // 新增视口重置回调
    glutReshapeFunc([](int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w/h, 0.1, 1000.0);
        glMatrixMode(GL_MODELVIEW);
    });
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // 设置灰色背景

    glutDisplayFunc([](){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        
        // 调试用临时立方体
        glColor3f(1,0,0);
        glutSolidCube(1);
        
        glutSwapBuffers();
    });

    glEnable(GL_COLOR_MATERIAL);  // 启用材质颜色跟踪
    glShadeModel(GL_SMOOTH);       // 平滑着色模式
    terrain.Generate();

    glutMotionFunc([](int x, int y) {
        static int lastX = 400, lastY = 300;
        float sensitivity = 0.1f;
        float dx = x - lastX;
        float dy = lastY - y;
        camera.yaw += dx * sensitivity;
        camera.pitch += dy * sensitivity;
        camera.UpdateFrontVector();
        lastX = x; lastY = y;
    });
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    // 新增调试重绘
    glutPostRedisplay();
    return 0;
}