#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
using namespace std;

float colors[6][3] = {
    {0.2f, 0.2f, 0.2f},
    {0.8f, 0.2f, 0.2f},
    {0.2f, 0.7f, 0.2f},
    {0.2f, 0.4f, 0.9f},
    {0.9f, 0.8f, 0.2f},
    {0.7f, 0.3f, 0.8f}
};

string colorNames[6] = {
    "Dark Gray", "Red", "Green", "Blue", "Yellow", "Purple"
};

int currentColor = 0;

void display() {
    glClearColor(colors[currentColor][0], colors[currentColor][1], colors[currentColor][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '6') {
        currentColor = key - '1'; 
        cout << "Selected Color: " << colorNames[currentColor] << endl;
        glutPostRedisplay();
    } else if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Keyboard Color Picker (Press 1-6 or ESC)");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}