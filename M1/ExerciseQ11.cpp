#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void drawCircleOutline(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    const int segments = 60;
    const float pi = 3.14159265f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = (float)i / segments * 2.0f * pi;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0f);

    drawCircleOutline(0.3f, 1.0f, 0.2f, 0.2f);
    drawCircleOutline(0.5f, 0.2f, 0.9f, 0.2f);
    drawCircleOutline(0.7f, 0.2f, 0.5f, 1.0f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Concentric Circles");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}