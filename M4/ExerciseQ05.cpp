#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawTriangleInt() {
    GLint triangleVertices[] = {
          0,  75, 0,
        -75, -50, 0,
         75, -50, 0
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_INT, 0, triangleVertices);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.3f, 0.2f);

    glPushMatrix();
        glScalef(0.01f, 0.01f, 1.0f);
        drawTriangleInt();
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q05 - GLint Vertex Data Type");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}