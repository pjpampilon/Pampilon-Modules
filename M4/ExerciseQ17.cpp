#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
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

void drawProceduralGear() {
    const int TEETH = 12;
    const int POINTS_PER_TOOTH = 4;
    const int SEGMENTS = TEETH * POINTS_PER_TOOTH;
    
    GLfloat vertices[(SEGMENTS + 1) * 3];
    
    GLubyte flatsIndices[(SEGMENTS / 2) * 3];
    GLubyte slopesIndices[(SEGMENTS / 2) * 3];

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for (int i = 0; i < SEGMENTS; ++i) {
        float radius = (i % 4 < 2) ? 0.75f : 0.50f;
        float angle = i * (2.0f * M_PI / SEGMENTS);
        
        int vIdx = (i + 1) * 3;
        vertices[vIdx]     = radius * cos(angle);
        vertices[vIdx + 1] = radius * sin(angle);
        vertices[vIdx + 2] = 0.0f;
    }

    int flatsCount = 0, slopesCount = 0;
    for (int i = 1; i <= SEGMENTS; ++i) {
        int next_i = (i == SEGMENTS) ? 1 : i + 1;
        
        if (i % 2 != 0) {
            flatsIndices[flatsCount++] = 0;      
            flatsIndices[flatsCount++] = i;      
            flatsIndices[flatsCount++] = next_i; 
        } else {
            slopesIndices[slopesCount++] = 0;
            slopesIndices[slopesCount++] = i;
            slopesIndices[slopesCount++] = next_i;
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glColor3f(0.75f, 0.75f, 0.8f);
    glDrawElements(GL_TRIANGLES, (SEGMENTS / 2) * 3, GL_UNSIGNED_BYTE, flatsIndices);

    glColor3f(0.4f, 0.4f, 0.45f);
    glDrawElements(GL_TRIANGLES, (SEGMENTS / 2) * 3, GL_UNSIGNED_BYTE, slopesIndices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawProceduralGear();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Procedural Gear Shape (Mechanical)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}