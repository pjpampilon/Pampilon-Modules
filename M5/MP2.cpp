// MP2: Community Park Layout Planner
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <array>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

struct Vertex { GLfloat x, y; };
static const array<Vertex, 20> vertices{{
    {-0.90f,-0.78f},
    {0.90f,-0.78f},
    {0.90f,0.78f},
    {-0.90f,0.78f},
    {-0.12f,-0.66f},
    {0.12f,-0.66f},
    {0.12f,0.66f},
    {-0.12f,0.66f},
    {-0.72f,0.18f},
    {-0.25f,0.18f},
    {-0.25f,0.58f},
    {-0.72f,0.58f},
    {0.30f,0.20f},
    {0.72f,0.20f},
    {0.72f,0.58f},
    {0.30f,0.58f},
    {0.30f,-0.58f},
    {0.72f,-0.58f},
    {0.72f,-0.22f},
    {0.30f,-0.22f}
}};
static const array<GLuint, 30> indices{{
    0,1,2, 0,2,3,  4,5,6, 4,6,7,  8,9,10, 8,10,11,
    12,13,14, 12,14,15, 16,17,18, 16,18,19
}};
GLuint vertexBuffer = 0, elementBuffer = 0;
atomic<bool> running{true};
mutex queueMutex;
queue<int> commands;
bool showPlayground = true, showGarden = true, showSeating = true;
int layout = 1;

void printMenu() {
    cout << "\n    Community Park Layout Planner    \n"
         << "1 Show All\n2 Toggle Playground\n3 Toggle Garden\n4 Toggle Seating\n"
         << "5 Layout A\n6 Layout B\n0 Exit\nChoice: " << flush;
}
void inputLoop() {
    while (running) {
        int choice;
        if (!(cin >> choice)) {
            if (running) { 
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                cout << "Invalid input. Enter a menu number.\n"; 
                printMenu(); }
            continue;
        }
        if (choice < 0 || choice > 6) {
            cout << "Invalid choice. Enter a number from 0 to 6.\n"; 
            printMenu(); 
            continue;
        }
        { 
            lock_guard<mutex> 
            lock(queueMutex); 
            commands.push(choice); 
        }
        if (choice == 0) break;
        printMenu();
    }
}
void setColorForFeature(int feature) {
    switch (feature) {
        case 0: glColor3f(0.83f,0.86f,0.79f); break; // park ground
        case 1: glColor3f(0.76f,0.68f,0.52f); break; // path
        case 2: glColor3f(0.92f,0.30f,0.22f); break; // playground
        case 3: glColor3f(0.25f,0.68f,0.34f); break; // garden
        case 4: glColor3f(0.24f,0.48f,0.82f); break; // seating
    }
}
void drawFeature(int feature, GLsizei firstIndex) {
    setColorForFeature(feature);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
                   reinterpret_cast<const void*>(static_cast<uintptr_t>(firstIndex * sizeof(GLuint))));
}
void drawText(float x, float y, const char* text, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* ch = text; *ch; ++ch)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *ch);
}
void drawLegend() {
    // text legend of park features
    drawText(-0.78f, -0.34f, "LEGEND", 0.12f, 0.15f, 0.13f);
    drawText(-0.78f, -0.43f, "Ground", 0.35f, 0.38f, 0.33f);
    drawText(-0.78f, -0.51f, "Walking Path", 0.58f, 0.48f, 0.28f);
    drawText(-0.78f, -0.59f, "Playground", 0.82f, 0.16f, 0.12f);
    drawText(-0.78f, -0.67f, "Garden", 0.13f, 0.45f, 0.20f);
    drawText(-0.78f, -0.75f, "Seating", 0.12f, 0.31f, 0.62f);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), nullptr);
    drawFeature(0, 0); // park boundary/ground
    drawFeature(1, 6); // walking path
    if (showPlayground) drawFeature(2, 12);
    if (showGarden) drawFeature(3, 18);
    if (showSeating) drawFeature(4, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    drawLegend();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glutSwapBuffers();
}
void applyChoice(int choice) {
    switch (choice) {
        case 1: showPlayground = showGarden = showSeating = true; break;
        case 2: showPlayground = !showPlayground; break;
        case 3: showGarden = !showGarden; break;
        case 4: showSeating = !showSeating; break;
        case 5: layout = 1; showPlayground = showGarden = showSeating = true; break;
        case 6: layout = 2; showPlayground = true; showGarden = false; showSeating = true; break;
        case 0: running = false; glDeleteBuffers(1, &vertexBuffer); glDeleteBuffers(1, &elementBuffer); 
        exit(EXIT_SUCCESS);
    }
    cout << "Layout " << (layout == 1 ? "A" : "B") << " | Playground: " << (showPlayground ? "shown" : "hidden")
              << ", Garden: " << (showGarden ? "shown" : "hidden") << ", Seating: " << (showSeating ? "shown" : "hidden") << '\n';
    glutPostRedisplay();
}
void pollCommands(int) {
    queue<int> pending;
    { 
        lock_guard<mutex> lock(queueMutex); 
        swap(pending, commands); 
    }
    while (!pending.empty()) { applyChoice(pending.front()); pending.pop(); }
    if (running) glutTimerFunc(50, pollCommands, 0);
}
void cleanup() {
    running = false;
    if (vertexBuffer) glDeleteBuffers(1, &vertexBuffer);
    if (elementBuffer) glDeleteBuffers(1, &elementBuffer);
}
int main(int argc, char** argv) {
    cout << "Legend: ground=light gray-green, path=tan, playground=red, garden=green, seating=blue.\n";
    printMenu();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 650);
    glutCreateWindow("Community Park Layout Planner - MP2");
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) { 
        cerr << "GLEW initialization failed.\n"; 
        return EXIT_FAILURE; 
    }
    glClearColor(0.12f,0.15f,0.18f,1.0f);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    atexit(cleanup);
    glutDisplayFunc(display);
    glutTimerFunc(50, pollCommands, 0);
    thread inputThread(inputLoop);
    glutMainLoop();
    running = false;
    if (inputThread.joinable()) inputThread.detach();
    return EXIT_SUCCESS;
}
