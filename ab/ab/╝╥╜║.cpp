#define WIDTH 400
#define HEIGHT 900

// 버블 이동 속도
#ifndef BUBBLE_SPEED_MULTIPLIER
#define BUBBLE_SPEED_MULTIPLIER 20
#endif

// 버블 발사 Y 좌표
#ifndef BUBBLE_LAUNCH_Y_COORD
#define BUBBLE_LAUNCH_Y_COORD -270
#endif

// 조명 효과
#ifndef LIGHTING_ON
#define LIGHTING_ON 0
#endif

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <GL/glut.h>
#include "Light.h"
#include "Board.h"
#include "Bubble.h"
#include "Cannon.h"

using namespace std;

#define M_PI 3.14159265358979323846

vector<Bubble> bubbles, drop;
Bubble b, nextBubble;
double theta = M_PI/2;
int cntShot = 0;
bool isShot = false, isDrop = false, isTransition = false;
int upper = 0;
double dx, dy;
clock_t start_clock = clock();
clock_t end_clock;

Light* light;

Board board = Board();

// cannon
Cannon cannon = Cannon();

void init() {
	srand(time(0));
	glEnable(GL_DEPTH_TEST);
	int option = rand() % 5;
	b = Bubble(25, 0, BUBBLE_LAUNCH_Y_COORD, option);
	option = rand() % 5;
	nextBubble = Bubble(25, -150, BUBBLE_LAUNCH_Y_COORD, option);
	// TODO: Initial scripts


	// lighting
	if (LIGHTING_ON){
		light = new Light(30.0, 200.0, 70.0, GL_LIGHT1);
		light->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
		light->setDiffuse(0.5f, 0.5f, 0.6f, 1.0f);
		light->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_LIGHTING);
    	light->draw();
	}

}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 32) {
		if(!isShot) {
			// 발사 각도에 따라 게임 속도가 느려지는거 보정
			dx = BUBBLE_SPEED_MULTIPLIER * cos(theta) ;
			dy = BUBBLE_SPEED_MULTIPLIER * sin(theta) ;
			b.changeDx(dx);
			b.changeDy(dy);
			cntShot++;
		}
		isShot = true;
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
		theta += 0.2/M_PI;
		theta = min(theta, M_PI / 180 * 170);
		break;
	case GLUT_KEY_RIGHT:
		theta -= 0.2/M_PI;
		theta = max(theta, M_PI / 180 * 10);
		break;
	}
	cannon.updateAngle(theta);
}

void idle() {
	/* Implement: check collision with boundary */
	end_clock = clock();
	if (end_clock - start_clock > 1000 / 60) {
		// update object
		if (isShot && !isTransition) {
			if (board.collision(b.getX(), b.getY(), b.getOption())) {
				board.BubblePop(b.getX(), b.getY(), b.getOption());
				drop = board.BubbleDrop();
				int option = rand() % 5;
				b = Bubble(25, 0, BUBBLE_LAUNCH_Y_COORD, nextBubble.getOption());
				nextBubble = Bubble(25, -150, BUBBLE_LAUNCH_Y_COORD, option);

				if (cntShot > 4 && cntShot % 5 == 0)	board.levelDown();
				isShot = false;
				if (drop.size() > 0) {
					isTransition = true;
					isDrop = true;
				}
				return;
			}
			if (b.getX() > 175 || b.getX() < -175) {
				dx = -1.0 * b.getDx();
				b.changeDx(dx);
			}
			b.move();
		}
		if (isDrop) {
			dx = 0.0;
			dy = -5.0;
			bool chk = true;
			vector<Bubble> tmp;
			for (auto bubble : drop) {
				bubble.move();
				bubble.changeDy(bubble.getDy() - 2.0);
				tmp.push_back(bubble);
				if (bubble.getY() >= -300)	chk = false;
			}
			drop = tmp;
			if (chk) {
				drop.clear();
				isTransition = false;
				isDrop = false;

			}
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
	for (auto bubble : drop)	bubble.draw();
	b.draw();
	nextBubble.draw();
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
	delete light;
	return 0;
}