#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

using namespace std;

bool stippleOn = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0f);

    if (stippleOn) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }

    glBegin(GL_LINE_LOOP);
        glColor3f(0.2f, 0.8f, 0.4f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();

    if (stippleOn) {
        glDisable(GL_LINE_STIPPLE);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 's' || key == 'S') {
        stippleOn = !stippleOn;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q17 - Toggle Stipple with Keyboard");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}