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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.0f, 0.5f, 0.0f);

        glVertex2f(0.0f, 0.0f);

        int numSegments = 7;
        float radius = 0.6f;

        for (int i = 0; i <= numSegments; ++i) {
            float angle = i * (M_PI / numSegments);
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex2f(x, y);
        }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q10 - Half-Circle Fan");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}