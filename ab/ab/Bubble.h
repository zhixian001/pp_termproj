#pragma once

#include <GL/glut.h>
#include "Material.h"

class Bubble{
public :
	/* op = option. Bubble's color */
	Bubble(double r = 0.0, double x = 0.0, double y = 0.0, int op = 0);
	void draw() const;
	void draw(int color) const;
	void move();
	void changeDx(double a) {
		dx = a;
	}
	void changeDy(double a) {
		dy = a;
	}
	double getX() const;
	double getY() const;
	double getDx() const {
		return dx;
	}
	double getDy() const {
		return dy;
	}
	int getOption() const;

private:
	double dx;
	double dy;
	double radius;
	double x, y;
	int option;
	Material mtl;
};
