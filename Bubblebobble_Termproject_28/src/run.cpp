#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <string>
#include <GL/glut.h>
#include <FreeImage.h>
#include "Settings.h"
#include "VisualBoard.h"
#include "Light.h"
#include "Board.h"
#include "Bubble.h"
#include "Cannon.h"
#include "TimeBar.h"
#include "Texture.h"

using namespace std;

#define M_PI 3.14159265358979323846

// Bubble b, nextBubble;
double theta = M_PI/2;
int cnt = 0;
double t = 0.0;
int upper = 0;

clock_t start_clock = clock();
clock_t end_clock;

Light* light0;
Light* light1;

vector<Texture> textures;


typedef enum
{
    InGame,
	GG,
	Clear
} ProgressStates;

ProgressStates g_state = InGame;
// Texture background

// Board board = Board();
VisualBoard* VB = new VisualBoard();

TimeBar tb = TimeBar();

int main_window, status_window, gameboard_window;


void draw_characters(void* font, const char* c, float x, float y) {
    /* TODO: Implement */
    glRasterPos2f(x, y);

    for (int i = 0; i < strlen(c); i++){
        glutBitmapCharacter(font, c[i]);
    }
}

void initGameBoard()
{
	// Background Texture
	Texture background = Texture("background.png");
	background.setTranslationfV(0.0, 0.06, -4.5);

	textures.push_back(background);


	// player texture
	Texture player0 = Texture("player0.png");
	Texture player1 = Texture("player1.png");

	player0.setTranslationfV(-1.6, -3, -2.5);
	player0.setFoV(110.0);

	player1.setTranslationfV(0.8, -2.0, -2.5);
	player1.setFoV(90.0);


	textures.push_back(player0);
	textures.push_back(player1);


	// init bubble game board
	while (VB->getBubble().size() == 2)
	{
		delete VB;
		VB = new VisualBoard();
	}
	srand(time(0));


	// lighting
	// if (LIGHTING_ON){
	light0 = new Light(0.0, 100.0, 300.0, GL_LIGHT0);
	light0->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light0->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light0->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	light1 = new Light(0, 0.0, 300.0, GL_LIGHT0);
	light1->setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light1->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light1->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

}

void initScoreBoard() {
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 32) {
		if (g_state == InGame) {
			VB->launchBubble();
		}
		else {
			exit(0);
		}
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:
			theta += 0.2/M_PI;
			theta = min(theta, M_PI / 180 * 170);
			VB->updateCannonAngle(theta);
			break;
		case GLUT_KEY_RIGHT:
			theta -= 0.2/M_PI;
			theta = max(theta, M_PI / 180 * 10);
			VB->updateCannonAngle(theta);
			break;
		case GLUT_KEY_F2:
			cout<<VB->getScore()<<endl;
			break;
	}
}

void idle() {
	end_clock = clock();
	if (end_clock - start_clock > 1000 / 60) {
		
		switch (g_state)
		{
		case InGame: {
			if (VB->gameClear())
			{
				Texture clearMsg = Texture("clear.png");
				clearMsg.setTranslationfV(0, 0.06, -4.5);
				clearMsg.setFoV(16);
				textures.push_back(clearMsg);
				g_state = Clear;
				cout << "Game Clear!" << endl;
			}

			if (VB->gameOver(upper))
			{
				Texture GGMsg = Texture("gg.png");
				GGMsg.setTranslationfV(0, 0.06, -4.5);
				GGMsg.setFoV(16);
				textures.push_back(GGMsg);
				g_state = GG;
				cout << "Game Over :(" << endl;

			}
			
			VB->stateTransition();
			if (VB->getState() == Ready) {
				if (tb.getTime() <= 0) VB->launchBubble();
				else tb.timeTicking();
			}
			else if (VB->getState() != ShotFlying) {
				tb.reset();
			}
			break;
		}
		case GG: {
			VB->stateTransition();
			
			break;
		}
		case Clear: {
			VB->stateTransition();

			break;
		}
		default:
		
			break;
		}		
	

		
		glutSetWindow(gameboard_window);
		glutPostRedisplay();
		glutSetWindow(status_window);
		glutPostRedisplay();
		start_clock = end_clock;
		
	}
}

void initParentWindow() {
	g_state = InGame;
}

void renderSceneParentWindow() {

}

void renderSceneGameBoard() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_SMOOTH);


	glPushMatrix();
	glTranslatef(30 * sin(t), 60, 0);
	VB->draw();

	// Draw Textures
	for (int i = 0 ; i < textures.size() ; i++) {
		textures[i].drawTexture();
	}

	glPopMatrix();

	light0->draw();
	light1->draw();
	


	glDisable(GL_LIGHTING);
	glDisable(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	

	glutSwapBuffers();
}

void renderSceneScoreBoard() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION); // Tell opengl that we are doing project matrix work
	glLoadIdentity(); // Clear the matrix
	glOrtho(-WIDTH/2, WIDTH/2, -15.0, 15.0, -100.0, 100.0); // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix

	string scoreTxt = to_string(VB->getScore());

	glPushMatrix();
	glColor3f(0,1,0);
	draw_characters(GLUT_BITMAP_HELVETICA_18, ("Score: " + scoreTxt).c_str(), -150, -7);
	glTranslatef(50, -6, 0);
		glColor3f(1,0,0);
	    draw_characters(GLUT_BITMAP_HELVETICA_18, "Time Left", 0, 6);
		tb.draw();
	glPopMatrix();

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
	glutInitWindowPosition(800, 100);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	main_window = glutCreateWindow("Class Term Project!");
		glutReshapeFunc(resize);
		glutIdleFunc(idle);
		initParentWindow();
		glutDisplayFunc(renderSceneParentWindow);
		
		// register callbacks
	gameboard_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, HEIGHT);
		initGameBoard();
		glutDisplayFunc(renderSceneGameBoard);
		glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(processSpecialKeys);
	status_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, 50);
		initScoreBoard();
		glutDisplayFunc(renderSceneScoreBoard);

	// int bottom_window = glutCreateSubWindow(main_window, 0, 850, 400, 50);

	// enter GLUT event processing cycle
	glutMainLoop();

	// exit
	delete light0;
	delete light1;
	delete VB;
	return 0;
}