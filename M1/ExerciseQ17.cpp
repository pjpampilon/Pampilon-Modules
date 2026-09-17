#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

int activeState = 0;

void drawLightCircle(float centerY, float r, float g, float b, bool isActive) {
    float brightness = isActive ? 1.0f : 0.25f;
    glColor3f(r * brightness, g * brightness, b * brightness);

    const int segments = 40;
    const float radius = 0.18f;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, centerY);
        for (int i = 0; i <= segments; i++) {
            float angle = (float)i / segments * 2.0f * 3.14159265f;
            glVertex2f(radius * cosf(angle), centerY + radius * sinf(angle));
        }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, -0.8f);
        glVertex2f(-0.3f,  0.8f);
        glVertex2f( 0.3f,  0.8f);
        glVertex2f( 0.3f, -0.8f);
    glEnd();

    drawLightCircle( 0.5f, 1.0f, 0.0f, 0.0f, activeState == 0);
    drawLightCircle( 0.0f, 1.0f, 0.9f, 0.0f, activeState == 1);
    drawLightCircle(-0.5f, 0.0f, 1.0f, 0.0f, activeState == 2);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'n' || key == 'N') {
        activeState = (activeState + 1) % 3;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 700);
    glutCreateWindow("Q17 - Traffic Light Simulator");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}