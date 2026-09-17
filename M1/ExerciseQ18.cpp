#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

float handAngle = 1.5707963f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    const int segments = 60;
    const float pi = 3.14159265f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float a = (float)i / segments * 2.0f * pi;
        glVertex2f(0.7f * cosf(a), 0.7f * sinf(a));
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        float a = (float)i / 12.0f * 2.0f * pi;
        glVertex2f(0.6f * cosf(a), 0.6f * sinf(a));
        glVertex2f(0.7f * cosf(a), 0.7f * sinf(a));
    }
    glEnd();

    glColor3f(1.0f, 0.2f, 0.2f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f * cosf(handAngle), 0.5f * sinf(handAngle));
    glEnd();

    glFlush();
}

void idle() {
    handAngle -= 0.0003f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q18 - Rotating Clock Hand");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}