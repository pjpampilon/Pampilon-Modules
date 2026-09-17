#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.84f, 0.0f);
    glLineWidth(2.0f);

    const int totalVertices = 10;
    const float rOuter = 0.7f;
    const float rInner = 0.3f;
    const float pi = 3.14159265f;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < totalVertices; i++) {
        float angle = (float)i / totalVertices * 2.0f * pi + (pi / 2.0f);

        float radius = (i % 2 == 0) ? rOuter : rInner;
        
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Five-Pointed Star Outline");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}