#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawTwoLines() {
    GLfloat lineVertices[] = {
        -0.75f,  0.4f, 0.0f,
         0.75f,  0.4f, 0.0f,

        -0.75f, -0.4f, 0.0f,
         0.75f, -0.4f, 0.0f
    };

    glLineWidth(4.0f);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, lineVertices);

    glDrawArrays(GL_LINES, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.1f);
    drawTwoLines();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q03 - Two Lines, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}