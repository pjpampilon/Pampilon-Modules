#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

float squareX = 0.0f;
float squareY = 0.0f;
const float squareSize = 0.15f;
const float step = 0.05f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.8f, 0.4f);
    glBegin(GL_POLYGON);
        glVertex2f(squareX - squareSize, squareY - squareSize);
        glVertex2f(squareX - squareSize, squareY + squareSize);
        glVertex2f(squareX + squareSize, squareY + squareSize);
        glVertex2f(squareX + squareSize, squareY - squareSize);
    glEnd();

    glFlush();
}

void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  squareX -= step;
    if (key == GLUT_KEY_RIGHT) squareX += step;
    if (key == GLUT_KEY_UP)    squareY += step;
    if (key == GLUT_KEY_DOWN)  squareY -= step;

    if (squareX - squareSize < -1.0f) squareX = -1.0f + squareSize;
    if (squareX + squareSize >  1.0f) squareX =  1.0f - squareSize;
    if (squareY - squareSize < -1.0f) squareY = -1.0f + squareSize;
    if (squareY + squareSize >  1.0f) squareY =  1.0f - squareSize;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Move Square with Arrow Keys");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}