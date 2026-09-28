#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*
 * Exercise Q18 - Keyboard-Switched Vertex Arrays [Hard]
 * Task: Switch between drawing a triangle, quad, or pentagon using 
 * keyboard inputs ('1', '2', '3'), utilizing global arrays to prevent 
 * rebuilding data every frame.
 */

// Global state tracking which shape is currently selected
int currentShape = 1; // Default to 1 (Triangle)

// 1. Declare shapes' vertex arrays as global data so they are built only once
GLfloat triangleVertices[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

GLfloat quadVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLfloat pentagonVertices[] = {
     0.0f,  0.6f, 0.0f,
    -0.57f, 0.18f, 0.0f,
    -0.35f, -0.5f, 0.0f,
     0.35f, -0.5f, 0.0f,
     0.57f, 0.18f, 0.0f
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    // 2. Branch on the global integer to choose which array/mode to draw
    if (currentShape == 1) {
        glColor3f(0.9f, 0.3f, 0.3f); // Red Triangle
        glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    } 
    else if (currentShape == 2) {
        glColor3f(0.3f, 0.8f, 0.3f); // Green Quad
        glVertexPointer(3, GL_FLOAT, 0, quadVertices);
        glDrawArrays(GL_QUADS, 0, 4);
    } 
    else if (currentShape == 3) {
        glColor3f(0.3f, 0.4f, 0.9f); // Blue Pentagon
        glVertexPointer(3, GL_FLOAT, 0, pentagonVertices);
        glDrawArrays(GL_POLYGON, 0, 5);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glFlush();
}

// 3. Keyboard callback to switch shapes
void keyboardMonitor(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            currentShape = 1;
            break;
        case '2':
            currentShape = 2;
            break;
        case '3':
            currentShape = 3;
            break;
    }
    
    // Mark the current window as needing to be redisplayed
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Q18 - Keyboard-Switched Vertex Arrays");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardMonitor); // Register the keyboard callback
    
    glutMainLoop();
    return 0;
}