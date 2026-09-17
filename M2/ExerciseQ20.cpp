#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

const int SEGMENT_COUNT = 60;

void setRainbowColor(float t) {
    float r = (sin(2.0f * M_PI * t) + 1.0f) * 0.5f;
    float g = (sin(2.0f * M_PI * t + (2.0f * M_PI / 3.0f)) + 1.0f) * 0.5f;
    float b = (sin(2.0f * M_PI * t + (4.0f * M_PI / 3.0f)) + 1.0f) * 0.5f;
    
    glColor3f(r, g, b);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);

        float radius = 0.7f;

        for (int i = 0; i <= SEGMENT_COUNT; ++i) {
            float t = static_cast<float>(i) / SEGMENT_COUNT;
            
            float angle = t * 2.0f * M_PI;

            setRainbowColor(t);

            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex2f(x, y);
        }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q20 - Procedural Rainbow Fan");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}