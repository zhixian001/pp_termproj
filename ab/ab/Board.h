#pragma once

#include <memory>
#include <cstring>
#include "Bubble.h"

class Board{
public:
	Board();
	void draw();
	std::pair<int, int> getPos(double x, double y);
	/* option : color */
	bool collision(double x, double y, int option);
	/* option : color */
	void BubblePop(double x, double y, int option);
	void BubbleDrop();

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
