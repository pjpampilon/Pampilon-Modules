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

    glShadeModel(GL_SMOOTH);

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex2f(0.0f, 0.7f);

        glColor3f(0.0f, 1.0f, 0.0f); 
        glVertex2f(0.7f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); 
        glVertex2f(0.0f, -0.7f);

        glColor3f(1.0f, 1.0f, 0.0f); 
        glVertex2f(-0.7f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q08 - Smooth Shaded Diamond");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}