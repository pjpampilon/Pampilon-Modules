#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

using namespace std;

float pulseValue = 0.0f;
float verticalOffset = 0.0f;

void renderText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    glutBitmapString(font, (const unsigned char*)text);
}

void drawPanel(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void creativeDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.08f, 0.09f, 0.12f, 1.0f); 

    void* normalFont = GLUT_BITMAP_HELVETICA_12;
    void* headerFont = GLUT_BITMAP_HELVETICA_18;


    glColor3f(0.5f + (sin(pulseValue) * 0.5f), 1.0f, 1.0f); 
    renderText(-0.95f, 0.85f + verticalOffset, "Enrollment Status : ENROLLED", headerFont);

    glColor3f(0.7f, 0.7f, 0.7f);
    renderText(-0.95f, 0.75f + verticalOffset, "Student # : 201411078", normalFont);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText(-0.95f, 0.68f + verticalOffset, "Name : PAMPILON, PATRICK", normalFont);
    

    glColor3f(0.0f, 0.8f, 1.0f);
    renderText(0.10f, 0.75f + verticalOffset, "College : COMPUTER STUDIES   Program : BSEMCDA", normalFont);
    glColor3f(0.8f, 0.8f, 0.8f);
    renderText(0.10f, 0.68f + verticalOffset, "Year Level : 3   1st term, SY 26-27", normalFont);

    float rowY = 0.35f + verticalOffset;

    glColor3f(0.12f, 0.15f, 0.22f); 
    drawPanel(-1.0f, rowY - 0.05f, 1.0f, rowY + 0.08f);

    glColor3f(1.0f, 0.85f, 0.2f);
    renderText(-0.95f, rowY, "Courses", headerFont);
    renderText(-0.70f, rowY, "Title", headerFont);
    renderText(0.00f,  rowY, "Section", headerFont);
    renderText(0.20f,  rowY, "Units", headerFont);
    renderText(0.35f,  rowY, "Days", headerFont);
    renderText(0.50f,  rowY, "Time", headerFont);
    renderText(0.80f,  rowY, "Room", headerFont);

    rowY -= 0.15f;

    glColor3f(0.8f, 0.9f, 0.9f);
    renderText(-0.90f, rowY, "CCS0021", normalFont);
    renderText(-0.70f, rowY, "INFORMATION MANAGEMENT (LEC)", normalFont);
    renderText(0.00f,  rowY, "TN25", normalFont);
    renderText(0.22f,  rowY, "2", normalFont);
    renderText(0.36f,  rowY, "T", normalFont);
    renderText(0.45f,  rowY, "13:00:00-15:40:00", normalFont);
    glColor3f(0.2f, 1.0f, 0.2f);
    renderText(0.80f,  rowY, "ONLINE", normalFont);

    rowY -= 0.10f;
    glColor3f(0.8f, 0.9f, 0.9f);
    renderText(-0.90f, rowY, "CCS0021L", normalFont);
    renderText(-0.70f, rowY, "INFORMATION MANAGEMENT (LAB)", normalFont);
    renderText(0.00f,  rowY, "TN25", normalFont);
    renderText(0.22f,  rowY, "1", normalFont);
    renderText(0.36f,  rowY, "F", normalFont);
    renderText(0.45f,  rowY, "13:00:00-15:50:00", normalFont);
    glColor3f(0.2f, 1.0f, 0.2f);
    renderText(0.80f,  rowY, "ONLINE", normalFont);

    rowY -= 0.10f;
    glColor3f(0.8f, 0.9f, 0.9f);
    renderText(-0.90f, rowY, "CS0045", normalFont);
    renderText(-0.70f, rowY, "CS ELECTIVE - COMPUTER GRAPHICS", normalFont);
    renderText(0.00f,  rowY, "TN35", normalFont);
    renderText(0.22f,  rowY, "3", normalFont);
    renderText(0.34f,  rowY, "M / TH", normalFont);
    renderText(0.45f,  rowY, "13:00:00-14:50:00...", normalFont);
    glColor3f(1.0f, 0.4f, 0.4f);
    renderText(0.80f,  rowY, "E601 / E610", normalFont);

    glColor3f(1.0f, 0.0f, 1.0f);
    renderText(-0.95f, -0.90f + verticalOffset, "TOTAL UNITS 9", headerFont);
    glColor3f(0.5f, 0.5f, 0.5f);
    renderText(0.50f, -0.90f + verticalOffset, "[ INTERACTIVE: Press 'W' to scroll up, 'S' to scroll down ]", normalFont);

    glFlush();
}


void animateStatus(int value) {
    pulseValue += 0.15f;
    glutPostRedisplay();
    glutTimerFunc(30, animateStatus, 0);
}


void keyboardMonitor(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
        case 'W':
            verticalOffset -= 0.05f;
            break;
        case 's':
        case 'S':
            verticalOffset += 0.05f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Interactive Dark Mode UI");
    
    glutDisplayFunc(creativeDisplay);
    
    glutKeyboardFunc(keyboardMonitor);
    glutTimerFunc(30, animateStatus, 0);
    
    glutMainLoop();
    return 0;
}