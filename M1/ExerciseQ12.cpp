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

    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.7f, 0.0f);
        glVertex2f( 0.3f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.3f,  0.2f);
        glVertex2f(0.3f, -0.2f);
        glVertex2f(0.7f,  0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q12 - Arrow");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}