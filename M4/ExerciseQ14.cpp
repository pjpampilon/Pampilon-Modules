#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawStaircase() {
    GLfloat vertices[] = {
        -0.75f, -0.60f, 0.0f,
        -0.75f, -0.30f, 0.0f,
        -0.30f, -0.60f, 0.0f,
        -0.30f, -0.30f, 0.0f,

        -0.25f, -0.20f, 0.0f,
        -0.25f,  0.10f, 0.0f,
         0.20f, -0.20f, 0.0f,
         0.20f,  0.10f, 0.0f,

         0.25f,  0.20f, 0.0f,
         0.25f,  0.50f, 0.0f,
         0.70f,  0.20f, 0.0f,
         0.70f,  0.50f, 0.0f
    };

    GLfloat colors[] = {
        0.9f, 0.2f, 0.2f,
        0.9f, 0.2f, 0.2f,
        0.9f, 0.2f, 0.2f,
        0.9f, 0.2f, 0.2f,

        0.2f, 0.8f, 0.2f,
        0.2f, 0.8f, 0.2f,
        0.2f, 0.8f, 0.2f,
        0.2f, 0.8f, 0.2f,

        0.2f, 0.4f, 0.9f,
        0.2f, 0.4f, 0.9f,
        0.2f, 0.4f, 0.9f,
        0.2f, 0.4f, 0.9f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_QUAD_STRIP, 0, 12);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStaircase();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q14 - Colored Quad Strip Staircase");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}