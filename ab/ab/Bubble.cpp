#include "Bubble.h"

float c[5][3] = { {0.7, 0.0, 0.0}, {0.0, 0.7, 0.0}, {0.0, 0.0, 0.7}, {0.7, 0.7, 0.0}, {0.7, 0.0, 0.7} };

Bubble::Bubble(double r, double px, double py, int op) {
	radius = r, x = px, y = py, option = op;	
}

void Bubble::move(double dx, double dy) {
	x += dx;
	y += dy;
}

double Bubble::getX() const {
	return x;
}

double Bubble::getY() const {
	return y;
}

int Bubble::getOption() const {
	return option;
}

void Bubble::draw() const {
	glPushMatrix();
	glColor3f(c[option][0], c[option][1], c[option][2]);
	glTranslatef(x, y, 50);
	glutSolidSphere(radius, 20, 50);
	glPopMatrix();
}

void Bubble::draw(int color) const {
	glPushMatrix();
	glColor3f(c[color][0], c[color][1], c[color][2]);
	glTranslatef(x, y, 50);
	glutSolidSphere(radius, 20, 50);
	glPopMatrix();
}