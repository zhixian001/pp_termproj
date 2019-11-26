#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <GL/glut.h>
#include "Settings.h"
#include "VisualBoard.h"
#include "Light.h"
#include "Board.h"
#include "Bubble.h"
#include "Cannon.h"
#include "TimeBar.h"

using namespace std;

#define M_PI 3.14159265358979323846

// Bubble b, nextBubble;
double theta = M_PI/2;
int cnt = 0;
// double t = 0.0;

clock_t start_clock = clock();
clock_t end_clock;

Light* light0;
Light* light1;

// Board board = Board();
VisualBoard VB = VisualBoard();

TimeBar tb = TimeBar();


int main_window, status_window, gameboard_window;

void initGameBoard() {
	// while (VB.getBubblez().size() == 2) {
	// VB = VisualBoard();
	// }
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	// TODO: Initial scripts
	// lighting
	if (LIGHTING_ON){
		light0 = new Light(200.0, 100.0, 500.0, GL_LIGHT0);
		light0->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		light0->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		light0->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

		light1 = new Light(200.0, 300.0, 500.0, GL_LIGHT0);
		light1->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		light1->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		light1->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

		glEnable(GL_LIGHTING);
		glEnable(GL_SMOOTH);
    	light0->draw();
    	light1->draw();
	}
}

void initScoreBoard() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 32) {
		VB.launchBubble();
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:
			theta += 0.2/M_PI;
			theta = min(theta, M_PI / 180 * 170);
			VB.updateCannonAngle(theta);
			break;
		case GLUT_KEY_RIGHT:
			theta -= 0.2/M_PI;
			theta = max(theta, M_PI / 180 * 10);
			VB.updateCannonAngle(theta);
			break;
		case GLUT_KEY_F2:
			cout<<VB.getScore()<<endl;
			break;
	}

}

void idle() {
	/* Implement: check collision with boundary */
	end_clock = clock();
	if (end_clock - start_clock > 1000 / 60) {
		
		cout << tb.getTime() << endl;
		// glutSetWindow(main_window);
		// glutPostRedisplay();
		if (VB.getState() > 1)	tb.reset();
		if (VB.getState() == 0)	tb.timeTicking();
		VB.stateTransition();
		if (tb.getTime() == 0 && VB.getState() == 0) {
			VB.launchBubble();
		}
		glutSetWindow(status_window);
		glutPostRedisplay();
		glutSetWindow(gameboard_window);
		glutPostRedisplay();
		start_clock = end_clock;
		// t += 0.2;
		// cout << t << endl;
		
	}
}

void initParentWindow() {

}

void renderSceneParentWindow() {

}

void renderSceneGameBoard() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -800 / 2, 800 / 2,-100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glPushMatrix();

	// glTranslatef(30*sin(t), 0, 0);
	VB.draw();
	// glPopMatrix();
	
	glutSwapBuffers();
}

void renderSceneScoreBoard() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION); // Tell opengl that we are doing project matrix work
	glLoadIdentity(); // Clear the matrix
	glOrtho(-200.0, 200.0, -50.0, 50.0, -100.0, 100.0); // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix

	// glPushMatrix();
	tb.draw();
	// glPopMatrix();

	glutSwapBuffers();
}


void resize(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow(WIDTH, HEIGHT);
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(650, 300);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	main_window = glutCreateWindow("Class Term Project!");
		glutReshapeFunc(resize);
		glutIdleFunc(idle);
		initParentWindow();
		glutDisplayFunc(renderSceneParentWindow);
		
		// register callbacks
	status_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, 100);
		initScoreBoard();
		 glutDisplayFunc(renderSceneScoreBoard);

	gameboard_window = glutCreateSubWindow(main_window, 0, 100, WIDTH, 800);
		initGameBoard();
		glutDisplayFunc(renderSceneGameBoard);
		glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(processSpecialKeys);

	// int bottom_window = glutCreateSubWindow(main_window, 0, 850, 400, 50);

	// enter GLUT event processing cycle
	glutMainLoop();


	// exit
	delete light0;
	delete light1;
	return 0;
}