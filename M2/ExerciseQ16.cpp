#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

void drawBase() {
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.6f, 0.3f); 

        glVertex2f(-0.02f, -0.7f);
        glVertex2f( 0.02f, -0.7f);
        glVertex2f( 0.22f,  0.0f);
        glVertex2f(-0.22f,  0.0f);
    glEnd();
}

void drawCircle() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.4f, 0.6f); 

        float cx = 0.0f;
        float cy = 0.2f;
        float radius = 0.3f;

        glVertex2f(cx, cy);

        int segments = 36;
        for (int i = 0; i <= segments; ++i) {
            float angle = i * (2.0f * M_PI / segments);
            float x = cx + radius * cos(angle);
            float y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBase();
    drawCircle();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q16 - Fan + Quad Composition");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}