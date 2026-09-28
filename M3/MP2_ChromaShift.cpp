#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum ColorCode { COLOR_RED = 0, COLOR_GREEN = 1, COLOR_BLUE = 2 };

const char* colorName(int c)
{
    switch (c)
    {
        case COLOR_RED:   return "RED";
        case COLOR_GREEN: return "GREEN";
        default:          return "BLUE";
    }
}

void applyColor(int c)
{
    switch (c)
    {
        case COLOR_RED:   glColor3f(1.0f, 0.15f, 0.15f); break;
        case COLOR_GREEN: glColor3f(0.15f, 1.0f, 0.15f); break;
        default:          glColor3f(0.15f, 0.45f, 1.0f); break;
    }
}

const float PLAYER_Y = -0.6f;
int playerColor = COLOR_RED;

float barrierY = 0.9f;
int   barrierColor = COLOR_GREEN;
float barrierSpeed = 0.008f;
const float BARRIER_MAX_SPEED = 0.03f;
bool  checkedThisPass = false; 

int  score = 0;
bool gameOver = false;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void spawnNextBarrier()
{
    barrierY = 0.9f;
    barrierColor = rand() % 3;
    checkedThisPass = false;
}

void drawPlayer()
{
    applyColor(playerColor);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, PLAYER_Y - 0.10f);
        glVertex2f( 0.15f, PLAYER_Y - 0.10f);
        glVertex2f( 0.15f, PLAYER_Y + 0.10f);
        glVertex2f(-0.15f, PLAYER_Y + 0.10f);
    glEnd();
}

void drawBarrier()
{
    applyColor(barrierColor);
    glBegin(GL_QUADS);
        glVertex2f(-0.9f, barrierY - 0.05f);
        glVertex2f( 0.9f, barrierY - 0.05f);
        glVertex2f( 0.9f, barrierY + 0.05f);
        glVertex2f(-0.9f, barrierY + 0.05f);
    glEnd();
}

void drawDashboard()
{
    char buffer[64];

    glColor3f(1.0f, 1.0f, 1.0f);
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    drawText(-0.95f, 0.90f, buffer);

    snprintf(buffer, sizeof(buffer), "Player Color: %s", colorName(playerColor));
    drawText(-0.95f, 0.80f, buffer);

    glColor3f(0.75f, 0.75f, 0.75f);
    drawText(-0.95f, -0.80f, "=== CONTROLS ===");
    drawText(-0.95f, -0.86f, "[R]/[G]/[B] Set Color   [X] Restart   [ESC] Exit");
    drawText(-0.95f, -0.92f, "Rule: a mismatch ends the game immediately.");

    if (gameOver)
    {
        glColor3f(1.0f, 0.3f, 0.3f);
        drawText(-0.32f, 0.0f, "MISMATCH - GAME OVER");
        drawText(-0.38f, -0.08f, "Press X to Restart");
    }
}

bool colorsMatch()
{
    return playerColor == barrierColor;
}

void checkGateCollision()
{
    if (checkedThisPass) return; 
    checkedThisPass = true;

    if (colorsMatch())
    {
        score++;
        barrierSpeed += 0.0015f;
        if (barrierSpeed > BARRIER_MAX_SPEED)
            barrierSpeed = BARRIER_MAX_SPEED;

        cout << "Match! Score: " << score
             << "  New speed: " << barrierSpeed << endl;

        spawnNextBarrier();
    }
    else
    {
        gameOver = true;
        cout << "Mismatch! Player was " << colorName(playerColor)
             << ", barrier was " << colorName(barrierColor)
             << ". GAME OVER." << endl;
    }
}

void resetGame()
{
    score = 0;
    gameOver = false;
    playerColor = COLOR_RED;
    barrierSpeed = 0.008f;
    spawnNextBarrier();
    cout << "Game reset." << endl;
}

void updateBarrier(int value)
{
    if (!gameOver)
    {
        barrierY -= barrierSpeed;

        if (barrierY <= PLAYER_Y + 0.10f && !checkedThisPass)
        {
            checkGateCollision();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBarrier, 0);
}

void display()
{
    glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver)
    {
        drawBarrier();
        drawPlayer();
    }

    drawDashboard();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'r':
        case 'R':
            if (!gameOver)
            {
                playerColor = COLOR_RED;
                cout << "Player color: RED" << endl;
            }
            break;

        case 'g':
        case 'G':
            if (!gameOver)
            {
                playerColor = COLOR_GREEN;
                cout << "Player color: GREEN" << endl;
            }
            break;

        case 'b':
        case 'B':
            if (!gameOver)
            {
                playerColor = COLOR_BLUE;
                cout << "Player color: BLUE" << endl;
            }
            break;

        case 'x':
        case 'X':
            resetGame();
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 2 - Chroma-Shift: The Color-Matching Gate");

    resetGame();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBarrier, 0);

    glutMainLoop();
    return 0;
}