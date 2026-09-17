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

    glBegin(GL_POLYGON);

        glColor3f(0.6f, 0.2f, 0.8f);

        glVertex2f( 0.0f,  0.6f);
        glVertex2f(-0.5f,  0.3f);
        glVertex2f(-0.5f, -0.3f);
        glVertex2f( 0.0f, -0.6f);
        glVertex2f( 0.5f, -0.3f);
        glVertex2f( 0.5f,  0.3f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q08 - Filled Hexagon");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}