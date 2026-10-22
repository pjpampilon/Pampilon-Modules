#include <GL/glew.h>
#include <GL/freeglut.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

struct Vertex { GLfloat x, y; };
struct Command { int choice; float step; };
static constexpr float HALF_SIZE = 0.055f;
static constexpr float MIN_BOUND = -0.84f;
static constexpr float MAX_BOUND = 0.84f;
static constexpr int AUTO_INTERVAL_MS = 350;

GLuint robotVbo = 0;

array<Vertex, 3> robotVertices{{{-0.055f,-0.055f},{0.055f,-0.055f},{0.0f,0.065f}}};
atomic<bool> running{true};
atomic<bool> autoMove{false};
mutex queueMutex;
queue<Command> commands;
float stepSize = 0.08f;
int autoDirection = 0;

void showMenu() {
    cout << "\n=== Warehouse Robot Route Simulator ===\n"
              << "1 Move Left\n2 Move Right\n3 Move Up\n4 Move Down\n"
              << "5 Set Step Size\n6 Return to Start\n7 Auto-Move Demo (toggle)\n0 Exit\nChoice: " << flush;
}
void inputLoop() {
    while (running) {
        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a menu number.\n"; showMenu(); continue;
        }

        if (choice < 0 || choice > 7) {
            cout << "Invalid choice. Enter a number from 0 to 7.\n"; showMenu(); continue;
        }

        float requestedStep = 0.0f;
        if (choice == 5) {
            cout << "Enter a positive step size (0.01 to 0.50): " << flush;
            if (!(cin >> requestedStep) || !isfinite(requestedStep) || requestedStep < 0.01f || requestedStep > 0.50f) {
                if (cin.eof()) break;
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Invalid step size. Use a number from 0.01 to 0.50.\n"; showMenu(); continue;
            }
        }
        { lock_guard<mutex> lock(queueMutex); commands.push({choice, requestedStep}); }
        if (choice == 0) break;
        showMenu();
    }
}

void drawText(float x, float y, const char* text, GLfloat r = 0.12f, GLfloat g = 0.14f, GLfloat b = 0.17f) {
    glColor3f(r,g,b); glRasterPos2f(x,y);
    for (const char* p = text; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
}

void drawRect(float x1, float y1, float x2, float y2, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r,g,b); glBegin(GL_QUADS);
    glVertex2f(x1,y1); glVertex2f(x2,y1); glVertex2f(x2,y2); glVertex2f(x1,y2);
    glEnd();
}

void drawWarehouse() {
    drawRect(-0.88f,-0.88f,0.88f,0.88f,0.91f,0.92f,0.88f);
    glLineWidth(3.0f); glColor3f(0.14f,0.18f,0.22f); glBegin(GL_LINE_LOOP);
    glVertex2f(-0.88f,-0.88f); glVertex2f(0.88f,-0.88f); glVertex2f(0.88f,0.88f); glVertex2f(-0.88f,0.88f);
    glEnd();
    // Destination zones
    drawRect(-0.76f,0.45f,-0.43f,0.72f,0.93f,0.67f,0.26f);
    drawRect(0.43f,0.45f,0.76f,0.72f,0.34f,0.70f,0.42f);
    drawRect(-0.16f,-0.72f,0.16f,-0.45f,0.33f,0.56f,0.86f);
    drawText(-0.73f,0.55f,"ZONE A",0.18f,0.14f,0.10f);
    drawText(0.47f,0.55f,"ZONE B",0.12f,0.18f,0.12f);
    drawText(-0.13f,-0.62f,"ZONE C",0.10f,0.15f,0.22f);
    drawText(-0.80f,0.79f,"WAREHOUSE ROUTE SIMULATOR",0.12f,0.14f,0.17f);
}
bool moveRobot(float dx, float dy) {
    // Keep the complete triangle inside the warehouse's movement limits.
    for (const auto& v : robotVertices) {
        if (v.x + dx < MIN_BOUND || v.x + dx > MAX_BOUND ||
            v.y + dy < MIN_BOUND || v.y + dy > MAX_BOUND) return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, robotVbo);
    auto* mapped = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
    if (!mapped) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        cerr << "Could not map robot VBO; position was not changed.\n";
        return false;
    }
    for (int i=0; i<3; ++i) { mapped[i].x += dx; mapped[i].y += dy; }
    const GLboolean ok = glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (ok != GL_TRUE) {
        cerr << "Robot VBO contents became invalid during update. Restoring start position.\n";
        robotVertices = {{{-0.055f,-0.055f},{0.055f,-0.055f},{0.0f,0.065f}}};
        glBindBuffer(GL_ARRAY_BUFFER, robotVbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(robotVertices), robotVertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return false;
    }
    for (auto& v : robotVertices) { v.x += dx; v.y += dy; }
    glutPostRedisplay();
    return true;
}

void autoTimer(int) {
    if (!running || !autoMove) return;
    static const float dxs[4] = {1.0f,0.0f,-1.0f,0.0f};
    static const float dys[4] = {0.0f,1.0f,0.0f,-1.0f};
    if (!moveRobot(dxs[autoDirection]*stepSize, dys[autoDirection]*stepSize))
        autoDirection = (autoDirection + 1) % 4;
    if (running && autoMove) glutTimerFunc(AUTO_INTERVAL_MS, autoTimer, 0);
}

void cleanup() {
    running = false;
    if (robotVbo) { glDeleteBuffers(1, &robotVbo); robotVbo = 0; }
}

void exitProgram() {
    autoMove = false; running = false;
    if (robotVbo) { glDeleteBuffers(1, &robotVbo); robotVbo = 0; }
    exit(EXIT_SUCCESS);
}

void applyCommand(Command command) {
    switch (command.choice) {
        case 1: autoMove=false; moveRobot(-stepSize,0.0f); break;
        case 2: autoMove=false; moveRobot(stepSize,0.0f); break;
        case 3: autoMove=false; moveRobot(0.0f,stepSize); break;
        case 4: autoMove=false; moveRobot(0.0f,-stepSize); break;
        case 5: autoMove=false; stepSize=command.step; cout << "Step size set to " << stepSize << ".\n"; break;
        case 6:
            autoMove=false;
            robotVertices = {{{-0.055f,-0.055f},{0.055f,-0.055f},{0.0f,0.065f}}};
            glBindBuffer(GL_ARRAY_BUFFER, robotVbo);
            glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(robotVertices),robotVertices.data());
            glBindBuffer(GL_ARRAY_BUFFER,0); glutPostRedisplay(); break;
        case 7:
            autoMove = !autoMove;
            if (autoMove) { autoDirection=0; glutTimerFunc(AUTO_INTERVAL_MS,autoTimer,0); }
            cout << (autoMove ? "Auto-move started.\n" : "Auto-move stopped.\n"); break;
        case 0: exitProgram(); break;
    }
}

void pollCommands(int) {
    queue<Command> pending;
    { lock_guard<mutex> lock(queueMutex); swap(pending,commands); }
    while (!pending.empty()) { applyCommand(pending.front()); pending.pop(); }
    if (running) glutTimerFunc(50,pollCommands,0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawWarehouse();
    glBindBuffer(GL_ARRAY_BUFFER,robotVbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2,GL_FLOAT,sizeof(Vertex),nullptr);
    glColor3f(0.77f,0.12f,0.16f);
    glDrawArrays(GL_TRIANGLES,0,3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    drawText(-0.80f,-0.96f,"Robot: red triangle | Destinations: A amber, B green, C blue",0.95f,0.95f,0.95f);
    glutSwapBuffers();
}

int main(int argc,char** argv) {
    cout << "Robot starts near the warehouse center. Moves stop at the boundary.\n";
    showMenu();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(900,700);
    glutCreateWindow("Warehouse Robot Route Simulator - MP3");
    glewExperimental=GL_TRUE;
    if (glewInit()!=GLEW_OK) { cerr << "GLEW initialization failed.\n"; return EXIT_FAILURE; }
    glClearColor(0.12f,0.15f,0.18f,1.0f);
    glGenBuffers(1,&robotVbo);
    glBindBuffer(GL_ARRAY_BUFFER,robotVbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(robotVertices),robotVertices.data(),GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    atexit(cleanup);
    glutDisplayFunc(display);
    glutTimerFunc(50,pollCommands,0);
    thread inputThread(inputLoop);
    inputThread.detach();
    glutMainLoop();
    running=false;
    return EXIT_SUCCESS;
}
