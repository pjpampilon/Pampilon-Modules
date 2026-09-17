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

    glBegin(GL_QUADS);

        glColor3f(0.2f, 0.6f, 1.0f);

        glVertex2f(-0.6f, -0.4f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.7f,  0.4f);
        glVertex2f(-0.3f,  0.6f);

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q07 - One Quadrilateral");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}