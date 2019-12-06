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

clock_t start_clock = clock();
clock_t end_clock;

Light light0;
Light light1;

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
	BaseObject txtcolor(5);
	//txtcolor.drawMaterialOnly();
	Material text_mtl;
	text_mtl.setEmission(0, 0, 0, 1);
	text_mtl.setAmbient(0, 1, 1, 1);
	text_mtl.setDiffuse(0, 0.5, 0.5, 1);
	text_mtl.setSpecular(0.5, 0.6, 0.6, 1);
	text_mtl.setShininess(50);
	glMaterialfv(GL_FRONT, GL_EMISSION, text_mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, text_mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, text_mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, text_mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, text_mtl.getShininess());


	glRasterPos2f(x, y);

    for (int i = 0; i < strlen(c); i++){
        glutBitmapCharacter(font, c[i]);
    }
}


void initGameBoard()
{
	// Background Texture
	textures.empty();

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
	while (VB->getBubble().size() <= 2)
	{
		delete VB;
		VB = new VisualBoard();
	}
	srand(time(0));

	cnt = 0;
	

}

void initScoreBoard() {
}

void processNormalKeys(unsigned char key, int x, int y) {

	// spacebar
	if (key == 32) {
		if (g_state == InGame) {
			VB->launchBubble();
			cnt++;
		}
		else {
			exit(0);
		}
	}
	// restart game
	if (key == 'r') {
		if (g_state == InGame) {
		}
		else {
			g_state = InGame;

			textures.resize(0);

			delete VB;

			VB = new VisualBoard();
			initGameBoard();
		}
	}
	// quick exit
	if (key == 'q') {
		exit(0);
	}
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:{
			if(g_state == InGame){
			theta += 0.2/M_PI;
			theta = min(theta, M_PI / 180 * 170);
			VB->updateCannonAngle(theta);
			}
			break;
			}
		case GLUT_KEY_RIGHT:{
			if(g_state == InGame){

			theta -= 0.2/M_PI;
			theta = max(theta, M_PI / 180 * 10);
			VB->updateCannonAngle(theta);
			}
			break;
			
		}
		case GLUT_KEY_F2:
			cout<<VB->getScore()<<endl;
			break;
		// Cheat!
		case GLUT_KEY_F12:{
			if(g_state == InGame){

			VB->cheatClear();
			cout << "You Cheated!!!" << endl;
			}
			break;
			}
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

			if (VB->gameOver())
			{
				Texture GGMsg = Texture("gg.png");
				GGMsg.setTranslationfV(0, 0.06, -4.5);
				GGMsg.setFoV(16);
				textures.push_back(GGMsg);
				g_state = GG;
				cout << "Game Over :(" << endl;

			}

			if (cnt == 8) {
				cout << "yes\n";
				VB->updateUpper();
				cnt = 0;
			}
			
			VB->stateTransition();
			if (VB->getState() == Ready) {
				if (tb.getTime() <= 0) VB->launchBubble(), cnt++;
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
		t += 0.4;
		glutSetWindow(main_window);
		glutPostRedisplay();		
		glutSetWindow(gameboard_window);
		glutPostRedisplay();
		glutSetWindow(status_window);
		glutPostRedisplay();
		start_clock = end_clock;
		
	}
}

void initParentWindow() {
	light0 = Light(0.0, 100.0, 300.0, GL_LIGHT0);
	light0.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light0.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light0.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	light1 = Light(0, 0.0, 300.0, GL_LIGHT0);
	light1.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light1.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	g_state = InGame;
}

void renderSceneParentWindow() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSetWindow(main_window);
	glutSwapBuffers();
}

void renderSceneGameBoard() {
	glutSetWindow(gameboard_window);
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
	glPopMatrix();

	// Draw Textures
	for (int i = 0 ; i < textures.size() ; i++) {
		textures[i].drawTexture();
	}

	glPopMatrix();

	light0.draw();
	light1.draw();
	


	glDisable(GL_LIGHTING);
	glDisable(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	

	glutSwapBuffers();
}

void renderSceneScoreBoard() {
	glutSetWindow(status_window);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -15.0, 15.0, -100.0, 100.0); // Setup an Ortho view

	string scoreTxt = to_string(VB->getScore());

	glPushMatrix();
	glTranslatef(0,0,10);

	glColor3f(0, 1, 0);
	draw_characters(GLUT_BITMAP_HELVETICA_18, ("Score: " + scoreTxt).c_str(), -150, -7);
	//draw_characters(GLUT_BITMAP_HELVETICA_18, ("Score: " + scoreTxt).c_str(), 0, 0);

	glTranslatef(50, -6, 0);
	glColor3f(1, 0, 0);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "Time Left", 0, 6);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
	status_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, 50);
		initScoreBoard();
		glutDisplayFunc(renderSceneScoreBoard);
	gameboard_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, HEIGHT);
		initGameBoard();
		glutDisplayFunc(renderSceneGameBoard);
		glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(processSpecialKeys);

	// int bottom_window = glutCreateSubWindow(main_window, 0, 850, 400, 50);

	// enter GLUT event processing cycle
	glutMainLoop();

	// exit
	delete VB;
	return 0;
}