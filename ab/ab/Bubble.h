#pragma once

#ifndef BOARD_HALF_WIDTH
#define BOARD_HALF_WIDTH 175
#endif
#ifndef BUBBLE_LAUNCH_Y_COORD
#define BUBBLE_LAUNCH_Y_COORD -270
#endif

#include <stdexcept>
#include <cstdlib>
#include <time.h>
#include <GL/glut.h>
#include "BaseObject.h"

typedef enum {Static, Flick, Falling, Moving, Dead} BubbleState;

class Bubble : public BaseObject{
public :
	/* op = option. Bubble's color */
	Bubble(double r = 0.0, double x = 0.0, double y = 0.0, int op = 0);
	void setState(BubbleState);
	void setState(BubbleState, double, double);
	BubbleState getState();
	void draw() const;
	// void draw(int color) const;
	void move();
	void moveRel (double rx=0, double ry=0);
	void moveAbs (double ax, double ay);
	void moveAbs (int ax, int ay);
	void changeDx(double a);
	void changeDy(double a);
	double getX() const;
	double getY() const;
	double getDx() const;
	double getDy() const;
	int getOption() const;

	int getRow() const;
	int getCol() const;
	void setRow(int);
	void setCol(int);

private:
	BubbleState state;
	double dx;
	double dy;
	double radius;
	double x, y;
	int option;
};
