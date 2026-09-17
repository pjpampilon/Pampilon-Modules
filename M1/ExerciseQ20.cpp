#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

const int STRIPE_COUNT = 7;

void drawStar(float cx, float cy, float rOuter, float rInner) {
    glColor3f(1.0f, 1.0f, 1.0f);
    const float pi = 3.14159265f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; i++) {
        float angleTip = i * (2.0f * pi / 5.0f) + (pi / 2.0f);

        float angleLeft  = angleTip - (pi / 5.0f);
        float angleRight = angleTip + (pi / 5.0f);

        float xTip = cx + rOuter * cosf(angleTip);
        float yTip = cy + rOuter * sinf(angleTip);

        float xLeft = cx + rInner * cosf(angleLeft);
        float yLeft = cy + rInner * sinf(angleLeft);

        float xRight = cx + rInner * cosf(angleRight);
        float yRight = cy + rInner * sinf(angleRight);

        glVertex2f(cx, cy);
        glVertex2f(xLeft, yLeft);
        glVertex2f(xTip, yTip);

        glVertex2f(cx, cy);
        glVertex2f(xTip, yTip);
        glVertex2f(xRight, yRight);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float totalHeight = 2.0f;
    float stripeHeight = totalHeight / STRIPE_COUNT;

    for (int i = 0; i < STRIPE_COUNT; i++) {
        float y0 = 1.0f - (i * stripeHeight);
        float y1 = y0 - stripeHeight;

        if (i % 2 == 0) {
            glColor3f(0.8f, 0.1f, 0.1f);
        } else {
            glColor3f(1.0f, 0.85f, 0.0f);
        }

        glBegin(GL_POLYGON);
            glVertex2f(-1.0f, y0);
            glVertex2f(-1.0f, y1);
            glVertex2f( 1.0f, y1);
            glVertex2f( 1.0f, y0);
        glEnd();
    }

    glColor3f(0.1f, 0.1f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f,  1.0f);
        glVertex2f(-1.0f,  0.1f);
        glVertex2f(-0.2f,  0.1f);
        glVertex2f(-0.2f,  1.0f);
    glEnd();

    drawStar(-0.6f, 0.55f, 0.18f, 0.07f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Q20 - Procedural Striped Flag with Star");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}