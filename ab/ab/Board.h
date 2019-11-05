#pragma once


// debugging 
#include <iostream>

#include <memory>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Bubble.h"

class Board{
public:
	Board();
	/* 새 맵 생성 후에 읽어오기 */
	std::vector<std::pair<Bubble*, std::pair<int, int>>> observeBoard();
	std::pair<int, int> getPos(double x, double y);
	/* option : color */
	std::pair<int, int> collision(const Bubble* bub);
	/* option : color */
	std::vector<std::pair<int, int>> BubblePop(const Bubble* bubs);
	std::vector<std::pair<int, int>> BubbleDropRC();
	void levelDown();
	std::pair<double, double> getCoords(int r, int c) const;
private:
	/* bubble visualization validity check */
	bool isValid(int row, int col);
	/* algorithmic validity check  */
	bool isValid2(int row, int col);
	/* dfs function. int option : color */
	void dfs(int row, int col, int option);
	bool visited[12][10];
	int upper;
	int stage;
	/* board array 버블들의 x 좌표값들 */
	double xPos[12][10];
	/* board array 버블들의 y 좌표값들 */
	double yPos[12][10];
	/* board array에 버블이 자리를 잡았는지 여부 */
	bool bubbled[12][10];
	/* board array에 자리잡은 버블의 색깔 */
	int color[12][10];
};
