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

    glShadeModel(GL_FLAT);

    glBegin(GL_QUAD_STRIP);

        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.8f,  0.3f);

        glColor3f(1.0f, 0.2f, 0.2f);
        glVertex2f(-0.48f, -0.3f);
        glVertex2f(-0.48f,  0.3f);

        glColor3f(0.2f, 0.8f, 0.2f);
        glVertex2f(-0.16f, -0.3f);
        glVertex2f(-0.16f,  0.3f);

        glColor3f(0.2f, 0.2f, 1.0f);
        glVertex2f( 0.16f, -0.3f);
        glVertex2f( 0.16f,  0.3f);

        glColor3f(1.0f, 1.0f, 0.2f);
        glVertex2f( 0.48f, -0.3f);
        glVertex2f( 0.48f,  0.3f);

        glColor3f(1.0f, 0.2f, 1.0f);
        glVertex2f( 0.8f, -0.3f);
        glVertex2f( 0.8f,  0.3f);

    glEnd();

    glShadeModel(GL_SMOOTH);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q18 - Alternating-Color Ribbon");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}