#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawCheckerboardRow() {
    GLfloat pool[] = {
        -0.8f, -0.2f, 0.0f,
        -0.8f,  0.2f, 0.0f,

        -0.4f, -0.2f, 0.0f,
        -0.4f,  0.2f, 0.0f,

         0.0f, -0.2f, 0.0f,
         0.0f,  0.2f, 0.0f,

         0.4f, -0.2f, 0.0f,
         0.4f,  0.2f, 0.0f,

         0.8f, -0.2f, 0.0f,
         0.8f,  0.2f, 0.0f
    };

    GLubyte quad1[] = { 0, 2, 3, 1 };
    GLubyte quad2[] = { 2, 4, 5, 3 };
    GLubyte quad3[] = { 4, 6, 7, 5 };
    GLubyte quad4[] = { 6, 8, 9, 7 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pool);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad1);

    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad2);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad3);

    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, quad4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCheckerboardRow();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Q10 - Checkerboard Row via glDrawElements");

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}