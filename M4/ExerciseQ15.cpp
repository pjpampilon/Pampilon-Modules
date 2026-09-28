#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawGround() {
    GLfloat groundVertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f, -0.2f, 0.0f,
        -1.0f, -0.2f, 0.0f
    };

    glColor3f(0.13f, 0.55f, 0.13f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    
    glDrawArrays(GL_QUADS, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawMountain() {
    GLfloat mountainVertices[] = {
        -0.8f, -0.2f, 0.0f,
         0.4f, -0.2f, 0.0f,
        -0.2f,  0.6f, 0.0f
    };

    glColor3f(0.5f, 0.5f, 0.55f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, mountainVertices);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawSun() {
    GLfloat sunVertices[] = {
         0.60f,  0.70f, 0.0f,
         0.60f,  0.85f, 0.0f,
         0.49f,  0.81f, 0.0f,
         0.45f,  0.70f, 0.0f,
         0.49f,  0.59f, 0.0f,
         0.60f,  0.55f, 0.0f,
         0.71f,  0.59f, 0.0f,
         0.75f,  0.70f, 0.0f,
         0.71f,  0.81f, 0.0f
    };

    GLubyte sunIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 1 };

    glColor3f(1.0f, 0.85f, 0.1f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, sunVertices);
    
    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_BYTE, sunIndices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawSun();
    drawMountain();
    drawGround();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q15 - Fully Array-Based Scene");
    
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}