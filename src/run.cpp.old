#define WIDTH 600
#define HEIGHT 1000

#include <GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST);

    // TODO: Initial scripts

}

void renderScene() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(30.0f, 30.0f, 30.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);


    /* TODO::Register Draw functions */

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(650, 300);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Class Term Project!");
    init();

    // register callbacks
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();


    // exit
    return 0;
}
