/**
 * @file Board.cpp
 * @author YHJeon
 * @brief Bubble Game board
 * @version 0.1
 * @date 2019-10-30
 * 
 * 보드 판 array에는 가로 10개, 세로 12개의 bubble이 들어간다.?
 * 알고리즘 구현의 편의를 위해 보이는 bubble은 가로 7~8, 세로 11개.
 * 
 * 두 개의 isValid 함수의 의미
 * 	게임 판은 아래와 같은 array.
 * 	logically invalid bubble: +, visually invalid bubble: X, logically & visually valid bubble: O
 * 
 * 			+ X X X X X X X X +
 * 			+ O O O O O O O + +
 * 			+ O O O O O O O O +
 * 			+ O O O O O O O + +
 * 			+ O O O O O O O O +
 * 			+ O O O O O O O + +
 * 			+ O O O O O O O O +
 * 			+ O O O O O O O + +
 * 			+ O O O O O O O O +
 * 			+ O O O O O O O + +
 * 			+ O O O O O O O O +
 * 			+ O O O O O O O + +
 * 
 * 	위의 array가 그려질 때는 아래처럼 그려짐
 * 
 * 		 01   O O O O O O O
 * 		 02  O O O O O O O O
 * 		 03   O O O O O O O 
 * 		 04  O O O O O O O O
 * 		 05   O O O O O O O
 * 		 06  O O O O O O O O
 * 		 07   O O O O O O O 
 * 		 08  O O O O O O O O
 * 		 09   O O O O O O O
 * 		 10  O O O O O O O O
 * 		 11   O O O O O O O
 * 
 * TOCHK: stage 변수의 사용? 게임판 내려오는거 구현용?
 */

#include "Board.h"
#include <cstdlib>
#include <time.h>
#define SQRT3 1.732050807568877293;

int dc[3] = { -1, 0, 1 };

Board::Board() {
	srand(time(0));
	upper = 275;
	stage = 1;
	for (int i = 0; i <= 11; i++) {
		xPos[i][0] = -25.0;
		if (i % 2 == 0)	xPos[i][0] += 25.0;
		for (int j = 1; j <= 8; j++) {
			xPos[i][j] = xPos[i][j - 1] + 50.0;
			yPos[i][j] = -(1.0 * i - 1.0) * 25.0 * SQRT3 - 25;
		}
	}
	memset(bubbled, false, sizeof(bubbled));
	memset(color, -1, sizeof(color));
	for (int i = 0; i <= 8; i++)	bubbled[0][i] = true, color[0][i] = 1;
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++) {
			if (!isValid(r, c))	continue;
			if (1.0 * rand()/ RAND_MAX < 0.7)	continue;
			bubbled[r][c] = true;
			color[r][c] = rand() % 5;
		}
	memset(visited, false, sizeof(visited));
	dfs(0, 1, -1);
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++) {
			if (!visited[r][c]) {
				bubbled[r][c] = false;
				color[r][c] = -1;
			}
		}
};

bool Board::isValid(int row, int col) {
	if (1 <= row && row <= 11 && 1 <= col && col <= 7)	return true;
	if (1 <= row && row <= 11 && col == 8 && row % 2)	return true;
	return false;
}

bool Board::isValid2(int row, int col) {
	if (0 <= row && row <= 11 && 1 <= col && col <= 7)	return true;
	if (0 <= row && row <= 11 && col == 8 && row % 2)	return true;
	return false;
}

std::pair<int, int> Board::getPos(double x, double y) {
	std::pair<int, int> ret = { -1, -1 };
	int dist = 987654321;
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++) {
			if (!isValid(r, c))	continue;
			if ((xPos[r][c] - 200 - 1.0 * x) * (xPos[r][c] - 200 - 1.0 * x) + (yPos[r][c] + upper - 1.0 * y) * (yPos[r][c] + upper - 1.0 * y) < dist) {
				dist = (xPos[r][c] - 200 - 1.0 * x) * (xPos[r][c] - 200 - 1.0 * x) + (yPos[r][c] + upper - 1.0 * y) * (yPos[r][c] + upper - 1.0 * y);
				ret = { r, c };
			}
		}
	return ret;
}

bool Board::collision(double x, double y, int option) {
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++) {
			if (!isValid2(r, c))	continue;
			if (y >= upper) {
				std::pair<int, int> coord = getPos(x, y);
				int r = coord.first;
				int c = coord.second;
				bubbled[r][c] = true;
				color[r][c] = option;
				return true;
			}
			if (!bubbled[r][c])	continue;
			double dist = (xPos[r][c]-200 - 1.0 * x) * (xPos[r][c]-200 - 1.0 * x) + (yPos[r][c]+upper - 1.0 * y) * (yPos[r][c]+upper - 1.0 * y);
			if (625 < dist && dist < 2500) {
				std::pair<int, int> coord = getPos(x, y);
				int r = coord.first;
				int c = coord.second;
				bubbled[r][c] = true;
				color[r][c] = option;
				return true;
			}
		}
	return false;
}

void Board::BubblePop(double x, double y, int option) {
	std::pair<int, int> coord = getPos(x, y);
	int r = coord.first;
	int c = coord.second;
	memset(visited, false, sizeof(visited));
	dfs(r, c, option);
	int cnt = 0;
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++)
			if (visited[r][c])	cnt++;
	if (cnt < 3)	return;
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++)
			if (visited[r][c]) {
				bubbled[r][c] = false;
				color[r][c] = -1;
			}
}

std::vector<Bubble> Board::BubbleDrop() {
	srand(time(0));
	std::vector<Bubble> ret;
	memset(visited, false, sizeof(visited));
	dfs(0, 1, -1);
	for (int r = 1; r <= 11; r++)
		for (int c = 1; c <= 8; c++)
			if (!visited[r][c] && bubbled[r][c]) {
				Bubble b = Bubble(25.0, xPos[r][c] - 200, yPos[r][c] + upper, color[r][c]);
				double dy = 1.0 * ((rand() % 30) - 10);
				double dx = 1.0 * ((rand() % 30) - 10) / 5;
				b.changeDx(dx);
				b.changeDy(dy);
				ret.push_back(b);
				bubbled[r][c] = false;
				color[r][c] = -1;
			}
	return ret;
}

void Board::dfs(int row, int col, int option) {
	visited[row][col] = true;
	if (row % 2) {
		for (int j = 0; j < 2; j++) {
			if (!isValid2(row + 1, col + dc[j]))	continue;
			if (!bubbled[row + 1][col + dc[j]])	continue;
			if (option != -1 && color[row + 1][col + dc[j]] != option)	continue;
			if (visited[row + 1][col + dc[j]])	continue;
			dfs(row + 1, col + dc[j], option);
		}
		for (int j = 0; j < 2; j++) {
			if (!isValid2(row - 1, col + dc[j]))	continue;
			if (!bubbled[row - 1][col + dc[j]])	continue;
			if (option != -1 && color[row - 1][col + dc[j]] != option)	continue;
			if (visited[row - 1][col + dc[j]] || color[row - 1][col + dc[j]] != option)	continue;
			dfs(row - 1, col + dc[j], option);
		}
		for (int j = 0; j < 3; j++) {
			if (!isValid2(row, col + dc[j]))	continue;
			if (!bubbled[row][col + dc[j]])	continue;
			if (option != -1 && color[row][col + dc[j]] != option)	continue;
			if (visited[row][col + dc[j]])	continue;
			dfs(row, col + dc[j], option);
		}
	}
	else {
		for (int j = 1; j < 3; j++) {
			if (!isValid2(row + 1, col + dc[j]))	continue;
			if (!bubbled[row + 1][col + dc[j]])	continue;
			if (option != -1 && color[row + 1][col + dc[j]] != option)	continue;
			if (visited[row + 1][col + dc[j]])	continue;
			dfs(row + 1, col + dc[j], option);
		}
		for(int j = 1;j<3;j++){
			if (!isValid2(row - 1, col + dc[j]))	continue;
			if (!bubbled[row - 1][col + dc[j]])	continue;
			if (option != -1 && color[row - 1][col + dc[j]] != option)	continue;
			if (visited[row - 1][col + dc[j]] || color[row - 1][col + dc[j]] != option)	continue;
			dfs(row - 1, col + dc[j], option);
		}
		for (int j = 0; j < 3; j++) {
			if (!isValid2(row, col + dc[j]))	continue;
			if (!bubbled[row][col + dc[j]])	continue;
			if (option != -1 && color[row][col + dc[j]] != option)	continue;
			if (visited[row][col + dc[j]])	continue;
			dfs(row, col + dc[j], option);
		}
	}
}

void Board::draw() {
	glPushMatrix();
	for(int r = 1; r<=11;r++)
		for (int c = 1; c <= 8; c++) {
			if (!isValid(r, c))	continue;
			if (!bubbled[r][c])	continue;
			Bubble b(25.0, xPos[r][c]-200, yPos[r][c]+upper);
			b.draw(color[r][c]);
		}
}