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

    const int gridCount = 4;
    float startX = -0.8f;
    float startY = -0.8f;
    float tileSize = 0.4f;

    for (int row = 0; row < gridCount; row++) {
        for (int col = 0; col < gridCount; col++) {

            if ((row + col) % 2 == 0) {
                glColor3f(0.9f, 0.9f, 0.9f);
            } else {
                glColor3f(0.1f, 0.1f, 0.1f);
            }

            float x0 = startX + col * tileSize;
            float y0 = startY + row * tileSize;
            float x1 = x0 + tileSize;
            float y1 = y0 + tileSize;

            glBegin(GL_POLYGON);
                glVertex2f(x0, y0);
                glVertex2f(x1, y0);
                glVertex2f(x1, y1);
                glVertex2f(x0, y1);
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - 4x4 Checkerboard");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}