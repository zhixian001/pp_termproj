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



Bubble::Bubble(double r, double px, double py, int op) : BaseObject(op) {
	radius = r;
	x = px;
	y = py;
	option = op;
	state = Static;
	// row = _row;
	// col = _col;

}

BubbleState Bubble::getState(){
	return state;
}

void Bubble::setState(BubbleState _state){
	if (_state == Falling){
		throw std::invalid_argument("Cannot change state 'Falling' directly");
	}
	else if (_state == Dead){
		throw std::invalid_argument("Cannot change state 'Dead' directly");
	}
	else if (_state == Moving){
		throw std::invalid_argument("Cannot change state 'Moving' without velocity");
	}
	else if (_state == Static) {
		dx = 0;
		dy = 0;
	}
	state = _state;
}

void Bubble::setState(BubbleState _state, double _dx, double _dy){
	if (_state == Moving && state != Moving){
		state = _state;
		dx = _dx;
		dy = _dy;
	}
	else {
		throw std::invalid_argument("Be Careful");
	}

}

void Bubble::move() {
	if (state == Static){}
	else if (state == Moving){
		x += dx;
		y += dy;
		// collision check
		if (x > BOARD_COLLISION_WIDTH || x < -BOARD_COLLISION_WIDTH){
			dx *= -1.0;
		}
	}
	else if (state == Falling){
		dy -= 2.0;
		x += dx;
		y += dy;
		// minimum y coord 보다 작으면 죽은 bubble
		if(y < BUBBLE_LAUNCH_Y_COORD){
			state = Dead;
		}
	}
	else if (state == Flick) {
		// flick
		dy = 1.0 * ((rand() % 30) - 10);
		dx = 1.0 * ((rand() % 30) - 10) / 5;
		state = Falling;
	}
	// dead
	else {

	}
}

void Bubble::moveRel(double rx, double ry) {
	x += rx;
	y += ry;
}
// Segfalut here!
void Bubble::moveAbs (double ax, double ay) {
	x = ax;
	y = ay;
}
void Bubble::moveAbs (int ax, int ay) {
	x = (double)ax;
	y = (double)ay;
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
	// 사라진 버블은 그리지 않음
	if (state == Dead) return;
	glPushMatrix();
	drawMaterial();
	glTranslatef(x, y, 50);
	glutSolidSphere(radius, 20, 50);
	glPopMatrix();
}

void Bubble::changeDx(double a) {
	dx = a;
}
void Bubble::changeDy(double a) {
	dy = a;
}

double Bubble::getDx() const {
	return dx;
}

double Bubble::getDy() const {
	return dy;
}
