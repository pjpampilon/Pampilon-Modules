#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*
 * Exercise Q19 - Interleaved + Indexed Hexagon [Hard]
 * Task: Combine interleaved arrays (position + color) with indexed 
 * rendering (glDrawElements) and a non-zero stride for a hexagon.
 */

void drawInterleavedIndexedHexagon() {
    // 1. Interleaved array for 6 vertices: [x, y, z, r, g, b]
    GLfloat hexData[] = {
         0.60f,  0.00f, 0.0f,   1.0f, 0.0f, 0.0f, // Index 0: Right (Red)
         0.30f,  0.52f, 0.0f,   1.0f, 1.0f, 0.0f, // Index 1: Top-Right (Yellow)
        -0.30f,  0.52f, 0.0f,   0.0f, 1.0f, 0.0f, // Index 2: Top-Left (Green)
        -0.60f,  0.00f, 0.0f,   0.0f, 1.0f, 1.0f, // Index 3: Left (Cyan)
        -0.30f, -0.52f, 0.0f,   0.0f, 0.0f, 1.0f, // Index 4: Bottom-Left (Blue)
         0.30f, -0.52f, 0.0f,   1.0f, 0.0f, 1.0f  // Index 5: Bottom-Right (Magenta)
    };

    // 2. Index array for GL_POLYGON
    GLubyte indices[] = { 0, 1, 2, 3, 4, 5 };

    // 3. Stride: Byte offset from one vertex to the next (6 floats total per vertex)
    GLsizei stride = 6 * sizeof(GLfloat);

    // Enable client states
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // 4. Set pointers: Position at offset 0, Color starting 3 floats in
    glVertexPointer(3, GL_FLOAT, stride, hexData);
    glColorPointer(3, GL_FLOAT, stride, hexData + 3);

    // 5. Draw the indexed polygon
    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, indices);

    // Disable client states
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawInterleavedIndexedHexagon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q19 - Interleaved + Indexed Hexagon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}