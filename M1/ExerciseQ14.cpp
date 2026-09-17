#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void drawSun() {
    glColor3f(1.0f, 0.85f, 0.2f);
    const int segments = 40;
    const float radius = 0.2f;
    const float cx = 0.6f;
    const float cy = 0.5f;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 2.0f * 3.14159265f;
            glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
        }
    glEnd();
}

void drawGround() {
    glColor3f(0.2f, 0.7f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f( 1.0f, -0.3f);
        glVertex2f( 1.0f, -1.0f);
    glEnd();
}

void display() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawSun();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Q14 - Simple Landscape");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}