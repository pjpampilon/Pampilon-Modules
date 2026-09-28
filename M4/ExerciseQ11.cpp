#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

const int SEGMENTS = 60;
const int TOTAL_VERTICES = SEGMENTS + 2;

void drawProceduralCircle() {
    GLfloat vertices[TOTAL_VERTICES * 3];
    GLfloat colors[TOTAL_VERTICES * 3];

    float radius = 0.65f;

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    colors[0] = 1.0f;
    colors[1] = 1.0f;
    colors[2] = 1.0f;

    for (int i = 0; i <= SEGMENTS; ++i) {
        float angle = i * (2.0f * M_PI / SEGMENTS);
        int idx = (i + 1) * 3;

        vertices[idx]     = radius * cos(angle);
        vertices[idx + 1] = radius * sin(angle);
        vertices[idx + 2] = 0.0f;

        colors[idx]     = 0.5f + 0.5f * cos(angle); 
        colors[idx + 1] = 0.5f + 0.5f * sin(angle);
        colors[idx + 2] = 0.5f + 0.5f * cos(angle + M_PI / 2.0f);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_TRIANGLE_FAN, 0, TOTAL_VERTICES);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawProceduralCircle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Procedural Shaded Circle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}