#define WIDTH 400
#define HEIGHT 900

// 버블 이동 속도
#ifndef BUBBLE_SPEED_MULTIPLIER
#define BUBBLE_SPEED_MULTIPLIER 7
#endif

// 버블 발사 Y 좌표
#ifndef BUBBLE_LAUNCH_Y_COORD
#define BUBBLE_LAUNCH_Y_COORD -270
#endif

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <GL/glut.h>
#include "Board.h"
#include "Bubble.h"
#include "Cannon.h"

using namespace std;

#define M_PI 3.14159265358979323846

vector<Bubble> bubbles;
Bubble b;
double theta = M_PI/2;
bool isShot = false;
int upper = 0;
double dx, dy;
clock_t start_clock = clock();
clock_t end_clock;

Board board = Board();

// cannon
Cannon cannon = Cannon();

void init() {
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	int option = rand() % 5;
	b = Bubble(25, 0, BUBBLE_LAUNCH_Y_COORD, option);
	// TODO: Initial scripts

}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 32) {
		if(!isShot) {
			// 발사 각도에 따라 게임 속도가 느려지는거 보정
			dx = BUBBLE_SPEED_MULTIPLIER * cos(theta) / cos(std::fabs(M_PI/2 - theta));
			dy = BUBBLE_SPEED_MULTIPLIER * sin(theta) / cos(std::fabs(M_PI/2 - theta));
		}
		isShot = true;
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
		theta += 0.2/M_PI;
		theta = min(theta, M_PI / 180 * 175);
		break;
	case GLUT_KEY_RIGHT:
		theta -= 0.2/M_PI;
		theta = max(theta, M_PI / 180 * 5);
		break;
	}
	cannon.updateAngle(theta);
}

void idle() {
	/* Implement: check collision with boundary */
	end_clock = clock();
	if (end_clock - start_clock > 1000 / 60) {
		// update object
		if (isShot) {
			if (board.collision(b.getX(), b.getY(), b.getOption())) {
				board.BubblePop(b.getX(), b.getY(), b.getOption());
				board.BubbleDrop();
				int option = rand() % 5;
				b = Bubble(25, 0, BUBBLE_LAUNCH_Y_COORD, option);
				isShot = false;
				return;
			}
			if (b.getX() > 175 || b.getX() < -175) {
				dx *= -1.0;
			}
			b.move(dx, dy);
		}
		start_clock = end_clock;
	}
	glutPostRedisplay();
}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Game Board
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex3f(-200, -240, 0.0);
	glVertex3f(-200, 300, 0.0);
	glVertex3f(200, 300, 0.0);
	glVertex3f(200, -240, 0.0);
	glEnd();

	
	/* TODO::Register Draw functions */
	
	double dx = 0.00, dy = 0.00005;
	glColor3f(0.8, 0.0, 0.0);
	
	b.draw();
	board.draw();
	cannon.draw();
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

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();


	// exit
	return 0;
}