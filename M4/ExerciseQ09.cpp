#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawIndexedPentagonFan() {
    GLfloat pentagonVertices[] = {
         0.00f,  0.00f, 0.0f,
         0.00f,  0.60f, 0.0f,
        -0.57f,  0.18f, 0.0f,
        -0.35f, -0.49f, 0.0f,
         0.35f, -0.49f, 0.0f,
         0.57f,  0.18f, 0.0f
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 1 };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, pentagonVertices);

    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.95f, 0.5f, 0.15f);
    drawIndexedPentagonFan();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q09 - Indexed Triangle Fan Pentagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}