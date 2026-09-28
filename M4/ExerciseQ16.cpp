#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

void drawArraysQuad() {
    GLfloat arraysVertices[] = {
        -0.8f, -0.4f, 0.0f,
        -0.1f, -0.4f, 0.0f,
        -0.1f,  0.4f, 0.0f,

        -0.8f, -0.4f, 0.0f,
        -0.1f,  0.4f, 0.0f,
        -0.8f,  0.4f, 0.0f
    };

    glColor3f(0.8f, 0.2f, 0.2f);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, arraysVertices);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawElementsQuad() {
    GLfloat elementsVertices[] = {
         0.1f, -0.4f, 0.0f,
         0.8f, -0.4f, 0.0f,
         0.8f,  0.4f, 0.0f,
         0.1f,  0.4f, 0.0f
    };

    GLubyte indices[] = { 
        0, 1, 2,
        0, 2, 3
    };

    glColor3f(0.2f, 0.4f, 0.9f);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, elementsVertices);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawArraysQuad();
    drawElementsQuad();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Q16 - glDrawArrays vs. glDrawElements");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}