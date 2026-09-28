#define GL_SILENCE_DEPRECATION
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

/*
 * Exercise Q20 - Capstone: Procedural Flower Scene [Hard]
 * Task: Build a procedurally generated flower (disc + petals) and a 
 * ground quad using a mix of procedural arrays, indexed drawing, 
 * and proper draw order.
 */

// --- Global Data Arrays ---

// 1. Ground Data
GLfloat groundVertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f, -0.3f, 0.0f,
    -1.0f, -0.3f, 0.0f
};

// 2. Petal Data (12 petals * 3 vertices * 3 floats)
const int NUM_PETALS = 12;
GLfloat petalVertices[NUM_PETALS * 9];
GLfloat petalColors[NUM_PETALS * 9];

// 3. Center Disc Data (30 segments + 1 center point)
const int DISC_SEGMENTS = 30;
GLfloat discVertices[(DISC_SEGMENTS + 1) * 3];
GLubyte discIndices[DISC_SEGMENTS + 2]; // Includes closing index

// --- Procedural Generation Functions ---

void generatePetals() {
    float centerX = 0.0f, centerY = 0.3f;
    float radius = 0.55f;
    float petalWidth = 0.15f; // Angle spread for outer corners

    for (int i = 0; i < NUM_PETALS; ++i) {
        float angle = i * (2.0f * M_PI / NUM_PETALS);
        int idx = i * 9;

        // Vertex 1: Flower Center
        petalVertices[idx]     = centerX;
        petalVertices[idx + 1] = centerY;
        petalVertices[idx + 2] = 0.0f;
        // Inner Color: White/Light Pink
        petalColors[idx] = 1.0f; petalColors[idx + 1] = 0.9f; petalColors[idx + 2] = 0.9f;

        // Vertex 2: Outer Corner 1
        petalVertices[idx + 3] = centerX + radius * cos(angle - petalWidth);
        petalVertices[idx + 4] = centerY + radius * sin(angle - petalWidth);
        petalVertices[idx + 5] = 0.0f;
        // Outer Color: Bright Pink
        petalColors[idx + 3] = 1.0f; petalColors[idx + 4] = 0.2f; petalColors[idx + 5] = 0.6f;

        // Vertex 3: Outer Corner 2
        petalVertices[idx + 6] = centerX + radius * cos(angle + petalWidth);
        petalVertices[idx + 7] = centerY + radius * sin(angle + petalWidth);
        petalVertices[idx + 8] = 0.0f;
        // Outer Color: Bright Pink
        petalColors[idx + 6] = 1.0f; petalColors[idx + 7] = 0.2f; petalColors[idx + 8] = 0.6f;
    }
}

void generateDisc() {
    float centerX = 0.0f, centerY = 0.3f;
    float radius = 0.12f;

    // Center Vertex
    discVertices[0] = centerX;
    discVertices[1] = centerY;
    discVertices[2] = 0.0f;
    discIndices[0] = 0; // Shared center index

    for (int i = 0; i < DISC_SEGMENTS; ++i) {
        float angle = i * (2.0f * M_PI / DISC_SEGMENTS);
        int vIdx = (i + 1) * 3;
        
        discVertices[vIdx]     = centerX + radius * cos(angle);
        discVertices[vIdx + 1] = centerY + radius * sin(angle);
        discVertices[vIdx + 2] = 0.0f;
        
        discIndices[i + 1] = i + 1; // Perimeter index
    }
    
    // Close the fan by pointing back to the first perimeter vertex
    discIndices[DISC_SEGMENTS + 1] = 1;
}

// --- Drawing Functions ---

void drawGround() {
    glColor3f(0.2f, 0.7f, 0.3f); // Green grass
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawPetals() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, petalVertices);
    glColorPointer(3, GL_FLOAT, 0, petalColors);
    
    // 12 petals * 3 vertices = 36 vertices total
    glDrawArrays(GL_TRIANGLES, 0, NUM_PETALS * 3);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drawDisc() {
    glColor3f(1.0f, 0.8f, 0.1f); // Golden yellow center
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, discVertices);
    glDrawElements(GL_TRIANGLE_FAN, DISC_SEGMENTS + 2, GL_UNSIGNED_BYTE, discIndices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw order matters: back to front
    drawGround();
    drawPetals();  // Draw petals before the disc
    drawDisc();    // Draw disc on top of petals
    
    glFlush();
}

int main(int argc, char** argv) {
    // Generate the procedural geometry once at startup
    generatePetals();
    generateDisc();

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Q20 - Capstone: Procedural Flower Scene");
    
    // Light blue sky background
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}