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
#include <string>

using namespace std;

float shipX = 0.0f;
float shipY = -0.75f;
const float SHIP_STEP = 0.05f;
const float SHIP_HALF_WIDTH = 0.08f;

struct Asteroid
{
    float x;
    float y;
    float speed;
    float size;
    bool  hit;
                        
};

const int NUM_ASTEROIDS = 3;
Asteroid asteroids[NUM_ASTEROIDS];

int  score = 0;
int  lives = 3;
bool gameOver = false;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void spawnAsteroid(int index)
{
    asteroids[index].x = -0.8f + static_cast<float>(rand() % 160) / 100.0f;
    asteroids[index].y = 1.0f + static_cast<float>(rand() % 50) / 100.0f;
    asteroids[index].hit = false;
}

void drawShip()
{
    glColor3f(0.2f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLES);
        glVertex2f(shipX,        shipY + 0.10f);
        glVertex2f(shipX - 0.08f, shipY - 0.08f);
        glVertex2f(shipX + 0.08f, shipY - 0.08f);
    glEnd();

    glColor3f(0.8f, 0.95f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(shipX - 0.02f, shipY - 0.02f);
        glVertex2f(shipX + 0.02f, shipY - 0.02f);
        glVertex2f(shipX + 0.02f, shipY + 0.04f);
        glVertex2f(shipX - 0.02f, shipY + 0.04f);
    glEnd();

    glColor3f(1.0f, 0.6f, 0.1f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
        glVertex2f(shipX - 0.04f, shipY - 0.10f);
        glVertex2f(shipX + 0.04f, shipY - 0.10f);
    glEnd();
}

void drawAsteroid(const Asteroid& a)
{
    glColor3f(0.65f, 0.45f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(a.x,            a.y + a.size);
        glVertex2f(a.x + a.size,   a.y + a.size * 0.4f);
        glVertex2f(a.x + a.size * 0.6f, a.y - a.size);
        glVertex2f(a.x - a.size * 0.6f, a.y - a.size);
        glVertex2f(a.x - a.size,   a.y + a.size * 0.4f);
    glEnd();
}

void drawHUD()
{
    char buffer[64];

    glColor3f(1.0f, 1.0f, 1.0f);
    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    drawText(-0.95f, 0.90f, buffer);

    snprintf(buffer, sizeof(buffer), "Lives: %d", lives);
    drawText(-0.95f, 0.80f, buffer);

    glColor3f(0.75f, 0.75f, 0.75f);
    drawText(-0.95f, -0.90f, "[A]/[D] Move  [W]/[S] Move  [R] Restart  [ESC] Exit");

    if (gameOver)
    {
        glColor3f(1.0f, 0.2f, 0.2f);
        drawText(-0.42f, 0.0f, "GAME OVER - Press R to Restart");
    }
}

bool checkCollision(const Asteroid& a)
{
    float dx = shipX - a.x;
    float dy = shipY - a.y;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    return dx < (SHIP_HALF_WIDTH + a.size * 0.6f) &&
           dy < (SHIP_HALF_WIDTH + a.size * 0.6f);
}

void resetGame()
{
    shipX = 0.0f;
    shipY = -0.75f;
    score = 0;
    lives = 3;
    gameOver = false;

    for (int i = 0; i < NUM_ASTEROIDS; i++)
    {
        spawnAsteroid(i);
        asteroids[i].speed = 0.006f + 0.004f * static_cast<float>(i);
        asteroids[i].size  = 0.06f;
    }

    cout << "Game reset. Lives: " << lives << ", Score: " << score << endl;
}

void updateGame(int value)
{
    if (!gameOver)
    {
        for (int i = 0; i < NUM_ASTEROIDS; i++)
        {
            asteroids[i].y -= asteroids[i].speed;

            if (!asteroids[i].hit && checkCollision(asteroids[i]))
            {
                asteroids[i].hit = true;
                lives--;
                cout << "Collision! Lives remaining: " << lives << endl;
                spawnAsteroid(i);

                if (lives <= 0)
                {
                    lives = 0;
                    gameOver = true;
                    cout << "GAME OVER. Final score: " << score << endl;
                }
            }
            else if (asteroids[i].y < -1.1f)
            {
                score++;
                spawnAsteroid(i);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

void display()
{
    if (gameOver)
        glClearColor(0.05f, 0.02f, 0.05f, 1.0f);
    else
        glClearColor(0.02f, 0.02f, 0.08f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver)
    {
        drawShip();
        for (int i = 0; i < NUM_ASTEROIDS; i++)
        {
            drawAsteroid(asteroids[i]);
        }
    }

    drawHUD();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            if (!gameOver) shipX -= SHIP_STEP;
            break;

        case 'd':
        case 'D':
            if (!gameOver) shipX += SHIP_STEP;
            break;

        case 'w':
        case 'W':
            if (!gameOver) shipY += SHIP_STEP;
            break;

        case 's':
        case 'S':
            if (!gameOver) shipY -= SHIP_STEP;
            break;

        case 'r':
        case 'R':
            resetGame();
            break;

        case 27: // ESC
            exit(0);
    }

    if (shipX > 0.92f)  shipX = 0.92f;
    if (shipX < -0.92f) shipX = -0.92f;
    if (shipY > 0.85f)  shipY = 0.85f;
    if (shipY < -0.90f) shipY = -0.90f;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 1 - The Cosmic Dodger");

    resetGame();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateGame, 0);

    glutMainLoop();
    return 0;
}
