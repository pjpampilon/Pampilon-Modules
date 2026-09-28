#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawSquareWithOutline() {
    GLfloat squareVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, squareVertices);

    glColor3f(0.2f, 0.5f, 0.9f);
    glDrawArrays(GL_QUADS, 0, 4);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquareWithOutline();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q04 - Square Plus Outline, Same Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}