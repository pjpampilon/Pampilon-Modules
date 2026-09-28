#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawIndexedPinwheel() {
    GLfloat vertices[] = {
         0.00f,  0.00f, 0.0f,
        -0.50f,  0.10f, 0.0f,
        -0.50f, -0.10f, 0.0f,
         0.50f,  0.10f, 0.0f, 
         0.50f, -0.10f, 0.0f,
        -0.10f,  0.50f, 0.0f,
         0.10f,  0.50f, 0.0f,
        -0.10f, -0.50f, 0.0f,
         0.10f, -0.50f, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    GLubyte indices[] = {
        0, 1, 2,
        0, 3, 4,
        0, 5, 6,
        0, 7, 8
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawIndexedPinwheel();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q13 - Pinwheel via glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}