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
#include <cmath>
#include <string>

using namespace std;

const float PI = 3.14159265f;

enum BurstType { BURST_SQUARES = 1, BURST_DIAMONDS = 2, BURST_STARBURST = 3 };

const char* typeName(int t)
{
    switch (t)
    {
        case BURST_SQUARES:  return "Concentric Squares";
        case BURST_DIAMONDS: return "Diamond Lattice";
        default:             return "Starburst Triangles";
    }
}

struct Burst
{
    bool  active;
    int   type;
    float x, y;
    float radius;
    float life;
};

const int MAX_BURSTS = 24;
Burst bursts[MAX_BURSTS];

const float MAX_RADIUS   = 0.55f;
const float EXPAND_SPEED = 0.010f;
const float FADE_SPEED   = 0.015f;

int lastMode = BURST_STARBURST;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void spawnBurst(int type, float x, float y)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (!bursts[i].active)
        {
            bursts[i].active = true;
            bursts[i].type   = type;
            bursts[i].x      = x;
            bursts[i].y      = y;
            bursts[i].radius = 0.02f;
            bursts[i].life   = 1.0f;
            lastMode = type;
            cout << "Spawned " << typeName(type) << " burst at ("
                 << x << ", " << y << ")" << endl;
            return;
        }
    }
    cout << "All burst slots are busy; try again shortly." << endl;
}

void spawnRandomBurst(int type)
{
    float x = -0.8f + static_cast<float>(rand() % 160) / 100.0f;
    float y = -0.7f + static_cast<float>(rand() % 140) / 100.0f;
    spawnBurst(type, x, y);
}

void drawConcentricSquares(const Burst& b)
{
    for (int ring = 1; ring <= 3; ring++)
    {
        float r = b.radius * (static_cast<float>(ring) / 3.0f);
        glColor3f(1.0f * b.life, 0.6f * b.life, 0.1f * b.life);
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x - r, b.y - r);
            glVertex2f(b.x + r, b.y - r);
            glVertex2f(b.x + r, b.y + r);
            glVertex2f(b.x - r, b.y + r);
        glEnd();
    }
}

void drawDiamondLattice(const Burst& b)
{
    for (int ring = 1; ring <= 3; ring++)
    {
        float r = b.radius * (static_cast<float>(ring) / 3.0f);
        glColor3f(0.2f * b.life, 0.6f * b.life, 1.0f * b.life);
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x,       b.y + r);
            glVertex2f(b.x + r,   b.y);
            glVertex2f(b.x,       b.y - r);
            glVertex2f(b.x - r,   b.y);
        glEnd();
    }
}

void drawStarburstTriangles(const Burst& b)
{
    const int spikes = 8;
    glColor3f(1.0f * b.life, 1.0f * b.life, 0.2f * b.life);

    for (int i = 0; i < spikes; i++)
    {
        float angle = (2.0f * PI * static_cast<float>(i)) / static_cast<float>(spikes);
        float tipX  = b.x + cosf(angle) * b.radius;
        float tipY  = b.y + sinf(angle) * b.radius;

        float baseAngle1 = angle + 0.12f;
        float baseAngle2 = angle - 0.12f;
        float baseR = b.radius * 0.55f;

        float base1X = b.x + cosf(baseAngle1) * baseR;
        float base1Y = b.y + sinf(baseAngle1) * baseR;
        float base2X = b.x + cosf(baseAngle2) * baseR;
        float base2Y = b.y + sinf(baseAngle2) * baseR;

        glBegin(GL_TRIANGLES);
            glVertex2f(tipX, tipY);
            glVertex2f(base1X, base1Y);
            glVertex2f(base2X, base2Y);
        glEnd();
    }
}

void drawBurst(const Burst& b)
{
    if (!b.active) return;

    switch (b.type)
    {
        case BURST_SQUARES:  drawConcentricSquares(b); break;
        case BURST_DIAMONDS: drawDiamondLattice(b);    break;
        default:              drawStarburstTriangles(b); break;
    }
}

void drawSidebar()
{
    int activeCount = 0;
    for (int i = 0; i < MAX_BURSTS; i++)
        if (bursts[i].active) activeCount++;

    char buffer[64];

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.98f, 0.92f, "=== FIREWORK & SHAPE BURST STUDIO ===");

    glColor3f(0.8f, 0.8f, 0.8f);
    drawText(-0.98f, 0.82f, "[SPACE] Random Burst");
    drawText(-0.98f, 0.74f, "[1] Concentric Squares");
    drawText(-0.98f, 0.66f, "[2] Diamond Lattice");
    drawText(-0.98f, 0.58f, "[3] Starburst Triangles");
    drawText(-0.98f, 0.50f, "[ESC] Exit");

    snprintf(buffer, sizeof(buffer), "Active Bursts: %d / %d", activeCount, MAX_BURSTS);
    drawText(-0.98f, 0.38f, buffer);

    snprintf(buffer, sizeof(buffer), "Last Mode: %s", typeName(lastMode));
    drawText(-0.98f, 0.30f, buffer);
}

void updateBursts(int value)
{
    for (int i = 0; i < MAX_BURSTS; i++)
    {
        if (!bursts[i].active) continue;

        bursts[i].radius += EXPAND_SPEED;
        bursts[i].life   -= FADE_SPEED;

        if (bursts[i].life <= 0.0f || bursts[i].radius >= MAX_RADIUS)
        {
            bursts[i].active = false;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, updateBursts, 0);
}

void display()
{
    glClearColor(0.03f, 0.03f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        drawBurst(bursts[i]);
    }

    drawSidebar();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
            spawnRandomBurst(lastMode == 0 ? BURST_STARBURST : lastMode);
            break;

        case '1':
            spawnRandomBurst(BURST_SQUARES);
            break;

        case '2':
            spawnRandomBurst(BURST_DIAMONDS);
            break;

        case '3':
            spawnRandomBurst(BURST_STARBURST);
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < MAX_BURSTS; i++)
    {
        bursts[i].active = false;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Machine Problem 3 - Dynamic Fireworks & Shape Burst Studio");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, updateBursts, 0);

    glutMainLoop();
    return 0;
}
