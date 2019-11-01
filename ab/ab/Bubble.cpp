/**
 * @file Bubble.cpp
 * @author YHJeon
 * @brief Bubble Game bubble
 * @version 0.1
 * @date 2019-10-30
 * 
 * 5종류의 버블이 있고, 변수 c 배열에 RGB 프리셋이 저장되어 있음
 * 버블
 * 	반지름: radius
 * 	현재 좌표: x, y
 * 	색깔(옵션): option
 * 
 * 움직임은 move 멤버로 delta 값 더함
 * 
 * 버블을 그리는 함수는 두 종류가 오버로딩 되어있음
 * 	draw()
 * 		이미 주어진 option 색으로 버블을 그림
 *  draw(int color)
 * 		새로운 색으로 버블 그림
 * 		아마 game over시 모든 버블의 색을 회색으로 바꾸는 등의 이펙트로 활용 가능할듯
 * 
 */
#include "Bubble.h"

float c[5][3] = { {0.7, 0.0, 0.0}, {0.0, 0.7, 0.0}, {0.0, 0.0, 0.7}, {0.7, 0.7, 0.0}, {0.7, 0.0, 0.7} };

Bubble::Bubble(double r, double px, double py, int op) {
	radius = r, x = px, y = py, option = op;	
}

void Bubble::move() {
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