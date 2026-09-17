#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f( 0.0f,  0.6f);
        glVertex2f( 0.5f,  0.3f);
        glVertex2f( 0.5f, -0.3f);
        glVertex2f( 0.0f, -0.6f);
        glVertex2f(-0.5f, -0.3f);
        glVertex2f(-0.5f,  0.3f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q06 - Hexagon Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}