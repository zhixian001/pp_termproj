#pragma once

#include <memory>
#include "bubble.h"

class Board{
public:
	Board();
	void draw();
	std::pair<int, int> getPos(double x, double y);
	bool collision(double x, double y, int option);
	void BubblePop(double x, double y, int option);
	void BubbleDrop();

private:
	bool isValid(int row, int col);
	bool isValid2(int row, int col);
	void dfs(int row, int col, int option);
	bool visited[12][10];
	int upper;
	int stage;
	double xPos[12][10];
	double yPos[12][10];
	bool bubbled[12][10];
	int color[12][10];
};

