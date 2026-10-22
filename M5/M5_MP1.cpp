// Click on the graphics window, then press a number key:
//   1 - Red     2 - Yellow     3 - Green     4 - Reset (all dark)     0 - Exit
// Any other key is rejected (message in the window and in the console).

#ifdef __APPLE__
  #define GL_SILENCE_DEPRECATION
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
#else
  #include <GL/glew.h>
  #include <GL/glut.h>
#endif

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

constexpr float PI = 3.14159265358979f;
constexpr int   CIRCLE_SEGMENTS = 48;                  // triangles per circle
constexpr int   CIRCLE_VERTS    = CIRCLE_SEGMENTS + 2; // center + ring + closing vertex

enum Signal { NONE = 0, RED = 1, YELLOW = 2, GREEN = 3 };

constexpr int HOUSING_FIRST = 0;                       // 6 verts (2 triangles)
constexpr int POLE_FIRST    = 6;                       // 6 verts (2 triangles)
constexpr int LAMP_FIRST[3] = {                        // red, yellow, green fans
    12,
    12 + CIRCLE_VERTS,
    12 + 2 * CIRCLE_VERTS
};
constexpr float LAMP_Y[3] = { 0.50f, 0.00f, -0.50f };  // top -> bottom
constexpr float LAMP_R    = 0.22f;

// state
GLuint      g_vbo      = 0;
Signal      g_active   = NONE;
float       g_aspect   = 480.0f / 720.0f;
std::string g_status   = "Press 1, 2, 3, 4 or 0";

// geometry
static void addQuad(std::vector<float>& v, float x0, float y0, float x1, float y1)
{
    const float q[12] = { x0,y0,  x1,y0,  x1,y1,   x0,y0,  x1,y1,  x0,y1 };
    v.insert(v.end(), q, q + 12);
}

static void addCircleFan(std::vector<float>& v, float cx, float cy, float r)
{
    v.push_back(cx); v.push_back(cy);                  // fan center
    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) {       // ring (last == first)
        float a = 2.0f * PI * i / CIRCLE_SEGMENTS;
        v.push_back(cx + r * std::cos(a));
        v.push_back(cy + r * std::sin(a));
    }
}

static std::vector<float> buildGeometry()
{
    std::vector<float> v;
    addQuad(v, -0.35f, -0.85f, 0.35f, 0.85f);          // housing
    addQuad(v, -0.06f, -1.00f, 0.06f, -0.85f);         // pole
    for (int i = 0; i < 3; ++i)                        // three lamps
        addCircleFan(v, 0.0f, LAMP_Y[i], LAMP_R);
    return v;
}

// drawing
static void drawText(float x, float y, const std::string& s)
{
    glRasterPos2f(x, y);
    for (char c : s) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
}

static void setLampColor(int lamp)
{
    // lamp: 0 = red, 1 = yellow, 2 = green
    static const float lit[3][3] = { {1.0f, 0.10f, 0.10f},
                                     {1.0f, 0.85f, 0.10f},
                                     {0.10f, 0.95f, 0.20f} };
    static const float dark[3]   = { 0.12f, 0.12f, 0.12f };

    if (g_active == lamp + 1) glColor3fv(lit[lamp]);
    else                      glColor3fv(dark);
}

static void display()
{
    glClearColor(0.55f, 0.75f, 0.95f, 1.0f);           // sky-blue background
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, nullptr);

    glColor3f(0.35f, 0.35f, 0.38f);                    // pole
    glDrawArrays(GL_TRIANGLES, POLE_FIRST, 6);

    glColor3f(0.05f, 0.05f, 0.05f);                    // housing
    glDrawArrays(GL_TRIANGLES, HOUSING_FIRST, 6);

    for (int i = 0; i < 3; ++i) {                      // lamps
        setLampColor(i);
        glDrawArrays(GL_TRIANGLE_FAN, LAMP_FIRST[i], CIRCLE_VERTS);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glColor3f(0.0f, 0.0f, 0.0f);
    float x = -g_aspect + 0.04f;
    drawText(x,  0.94f, "1 - Red");
    drawText(x,  0.88f, "2 - Yellow");
    drawText(x,  0.82f, "3 - Green");
    drawText(x,  0.76f, "4 - Reset");
    drawText(x,  0.70f, "0 - Exit");
    drawText(x, -0.96f, g_status);

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    g_aspect = static_cast<float>(w) / h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-g_aspect, g_aspect, -1.0, 1.0, -1.0, 1.0); // keeps circles round
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// input
static void quitProgram()
{
    std::cout << "Exiting. Goodbye!\n";
    glDeleteBuffers(1, &g_vbo);
    std::exit(EXIT_SUCCESS);
}

static void keyboard(unsigned char key, int, int)
{
    switch (key) {
        case '1': g_active = RED;    g_status = "RED - Stop";                break;
        case '2': g_active = YELLOW; g_status = "YELLOW - Prepare to stop"; break;
        case '3': g_active = GREEN;  g_status = "GREEN - Go";               break;
        case '4': g_active = NONE;   g_status = "Reset - all lights off";   break;
        case '0':
        case 27:  quitProgram();     return;                                // 0 or ESC
        default:
            g_status = "Invalid key. Use 1, 2, 3, 4 or 0.";
            std::cout << "Invalid selection. Use 1, 2, 3, 4 or 0.\n";
            glutPostRedisplay();
            return;
    }
    std::cout << "Display updated: " << g_status << "\n";
    glutPostRedisplay();
}

// main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(480, 720);
    glutCreateWindow("Campus Traffic Signal Visualizer");

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return EXIT_FAILURE;
    }
#endif

    // Upload all vertex positions to one VBO
    std::vector<float> vertices = buildGeometry();
    glGenBuffers(1, &g_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "Click the graphics window, then press: "
                 "1=Red  2=Yellow  3=Green  4=Reset  0=Exit\n";

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return EXIT_SUCCESS;
}