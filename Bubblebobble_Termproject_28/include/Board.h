#pragma once

// debugging
#include <iostream>

#include <memory>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Settings.h"
#include "Bubble.h"

#ifndef WIDTH
#define WIDTH 400
#endif

#ifndef GAME_ROW_COUNT
// #define GAME_ROW_COUNT 16
#define GAME_ROW_COUNT 12
#endif

#ifndef GAME_COLUMN_COUNT
#define GAME_COLUMN_COUNT 10
#endif

#ifndef DEFAULT_UPPER_COORD
// #define DEFAULT_UPPER_COORD 375
#define DEFAULT_UPPER_COORD 275
#endif

#ifndef BUBBLE_RADIUS
#define BUBBLE_RADIUS 25.0
#endif

class Board
{
public:
	Board();
	/* 새 맵 생성 후에 읽어오기 */
	std::vector<std::pair<Bubble *, std::pair<int, int>>> observeBoard();
	std::pair<int, int> getPos(double x, double y);
	/* option : color */
	std::pair<int, int> collision(const Bubble *bub);
	/* option : color */
	std::vector<std::pair<int, int>> BubblePop(const Bubble *bubs);
	std::vector<std::pair<int, int>> BubbleDropRC();
	void levelDown();
	std::pair<double, double> getCoords(int r, int c) const;
	void cheatClear();
	
	bool checkGameOver(int row_down=0);

private:
	const double bubble_diameter = BUBBLE_RADIUS * 2;
	/* bubble visualization validity check */
	bool isValid(int row, int col);
	/* algorithmic validity check  */
	bool isValid2(int row, int col);
	/* dfs function. int option : color */
	void dfs(int row, int col, int option);
	bool visited[GAME_ROW_COUNT][GAME_COLUMN_COUNT];
	int upper;
	int stage;
	/* board array 버블들의 x 좌표값들 */
	double xPos[GAME_ROW_COUNT][GAME_COLUMN_COUNT];
	/* board array 버블들의 y 좌표값들 */
	double yPos[GAME_ROW_COUNT][GAME_COLUMN_COUNT];
	/* board array에 버블이 자리를 잡았는지 여부 */
	bool bubbled[GAME_ROW_COUNT][GAME_COLUMN_COUNT];
	/* board array에 자리잡은 버블의 색깔 */
	int color[GAME_ROW_COUNT][GAME_COLUMN_COUNT];
};
