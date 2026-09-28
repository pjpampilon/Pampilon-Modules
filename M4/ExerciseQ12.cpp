#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;


void drawInterleavedQuad() {
    GLfloat quadData[] = {
        -0.6f, -0.6f, 0.0f,  1.0f, 0.2f, 0.2f,
         0.6f, -0.6f, 0.0f,  0.2f, 1.0f, 0.2f,
         0.6f,  0.6f, 0.0f,  0.2f, 0.4f, 1.0f,
        -0.6f,  0.6f, 0.0f,  1.0f, 1.0f, 0.2f
    };

    GLsizei stride = 6 * sizeof(GLfloat);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, stride, quadData);
    glColorPointer(3, GL_FLOAT, stride, quadData + 3);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawInterleavedQuad();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q12 - Interleaved Array Quad");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}