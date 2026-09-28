#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawThreeTriangles() {
    GLfloat triangleVertices[] = {
        -0.85f, -0.4f, 0.0f,
        -0.55f,  0.4f, 0.0f,
        -0.25f, -0.4f, 0.0f,

        -0.30f, -0.4f, 0.0f,
         0.00f,  0.4f, 0.0f,
         0.30f, -0.4f, 0.0f,

         0.25f, -0.4f, 0.0f,
         0.55f,  0.4f, 0.0f,
         0.85f, -0.4f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);

    glDrawArrays(GL_TRIANGLES, 0, 9);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.3f, 0.85f, 0.4f);
    drawThreeTriangles();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Q08 - Three Triangles, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}