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

#define SQRT3 1.732050807568877293;

int dc[3] = {-1, 0, 1};

Board::Board()
{
	srand(time(0));
	upper = DEFAULT_UPPER_COORD;
	stage = 1;
	for (int i = 0; i <= GAME_ROW_COUNT - 1; i++)
	{
		xPos[i][0] = -BUBBLE_RADIUS;
		if (i % 2 == 0)
			xPos[i][0] += BUBBLE_RADIUS;
		for (int j = 1; j <= GAME_COLUMN_COUNT - 2; j++)
		{
			xPos[i][j] = xPos[i][j - 1] + bubble_diameter;
			yPos[i][j] = -(1.0 * i - 1.0) * BUBBLE_RADIUS * SQRT3 - BUBBLE_RADIUS;
		}
	}
	memset(bubbled, false, sizeof(bubbled));
	memset(color, -1, sizeof(color));

	// 맵 생성
	for (int i = 0; i <= GAME_COLUMN_COUNT - 2; i++)
	{
		bubbled[0][i] = true;
		color[0][i] = 0;
	}
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
	{
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
		{
			if (!isValid(r, c))
				continue;
			if (1.0 * rand() / RAND_MAX < 0.7)
				continue;
			bubbled[r][c] = true;
			color[r][c] = rand() % 5 + 1;
		}
	}
	memset(visited, false, sizeof(visited));
	dfs(0, 1, -1);
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
	{
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
		{
			if (!visited[r][c])
			{
				bubbled[r][c] = false;
				color[r][c] = -1;
			}
		}
	}
}

std::vector<std::pair<Bubble *, std::pair<int, int>>> Board::observeBoard()
{
	std::vector<std::pair<Bubble *, std::pair<int, int>>> observation;

	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
	{
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
		{
			if (isValid(r, c) && bubbled[r][c])
			{
				observation.push_back({new Bubble(BUBBLE_RADIUS, xPos[r][c] - (WIDTH / 2), yPos[r][c] + upper, color[r][c]), {r, c}});
			}
		}
	}
	return observation;
}

bool Board::isValid(int row, int col)
{
	if (row >= 1 && row <= GAME_ROW_COUNT -1 && col >= 1 && col <= GAME_COLUMN_COUNT -3){
		return true;
	}
	else if (row >= 1 && row <= GAME_ROW_COUNT -1 && col == GAME_COLUMN_COUNT -2 && row % 2) {
		return true;
	}
	else {
		return false;
	}


	// if (1 <= row && row <= GAME_ROW_COUNT - 1 && 1 <= col && col <= GAME_COLUMN_COUNT - 3)
		// return true;
	// if (col == GAME_COLUMN_COUNT - 2 && row % 2)
		// return true;
	// return false;
}

bool Board::isValid2(int row, int col)
{
	if (0 <= row && row <= GAME_COLUMN_COUNT - 1 && 1 <= col && col <= GAME_COLUMN_COUNT - 3)
		return true;
	if (0 <= row && row <= GAME_ROW_COUNT - 1 && col == GAME_COLUMN_COUNT - 2 && row % 2)
		return true;
	return false;
	// if (isValid(row, col)) {
	// 	return true;
	// }
	// else if (row >= 0 && row < GAME_ROW_COUNT -1 ) {
	// 	return true;
	// }
	// else {
	// 	return false;
	// }
	// else if (col == GAME_COLUMN_COUNT - 2 && row % 2)

	// if (0 <= row && row <= GAME_ROW_COUNT - 1 && 1 <= col && col <= GAME_COLUMN_COUNT - 3)
	// 	return true;
	// if (0 <= row && row <= GAME_ROW_COUNT - 1 && col == GAME_COLUMN_COUNT - 2 && row % 2)
	// 	return true;
	// return false;
}

std::pair<int, int> Board::getPos(double x, double y)
{
	std::pair<int, int> ret = {-1, -1};
	int dist = INT32_MAX;
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
		{
			if (!isValid(r, c))
				continue;
			if ((xPos[r][c] - (WIDTH / 2) - 1.0 * x) * (xPos[r][c] - (WIDTH / 2) - 1.0 * x) + (yPos[r][c] + upper - 1.0 * y) * (yPos[r][c] + upper - 1.0 * y) < dist)
			{
				dist = (xPos[r][c] - (WIDTH / 2) - 1.0 * x) * (xPos[r][c] - (WIDTH / 2) - 1.0 * x) + (yPos[r][c] + upper - 1.0 * y) * (yPos[r][c] + upper - 1.0 * y);
				ret = {r, c};
			}
		}
	return ret;
}

void Board::levelDown()
{
	upper -= bubble_diameter;
}

std::pair<int, int> Board::collision(const Bubble *bub)
{


	double x = bub->getX();
	double y = bub->getY();
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
	{
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
		{
			if (!isValid2(r, c)) continue;
			if (y >= upper)
			{
				std::pair<int, int> coord = getPos(x, y);
				int r = coord.first;
				int c = coord.second;
				bubbled[r][c] = true;
				color[r][c] = bub->getOption();
				return {r, c};
			}
			if (!bubbled[r][c]) continue;

			double dist = (xPos[r][c] - (WIDTH / 2) - 1.0 * x) * (xPos[r][c] - (WIDTH / 2) - 1.0 * x) + (yPos[r][c] + upper - 1.0 * y) * (yPos[r][c] + upper - 1.0 * y);
			// TOCHK: generalize?
			if (dist > 625 && dist < 2500)
			{
				std::pair<int, int> coord = getPos(x, y);
				int r = coord.first;
				int c = coord.second;
				bubbled[r][c] = true;
				color[r][c] = bub->getOption();
				return {r, c};
			}
		}
	}
	return {-1, -1};
}

std::pair<double, double> Board::getCoords(int r, int c) const
{
	return {xPos[r][c] - (WIDTH / 2), yPos[r][c] + upper};
}

std::vector<std::pair<int, int>> Board::BubblePop(const Bubble *bub)
{
	std::vector<std::pair<int, int>> ret;
	double x = bub->getX();
	double y = bub->getY();
	std::pair<int, int> coord = getPos(x, y);
	int r = coord.first;
	int c = coord.second;
	memset(visited, false, sizeof(visited));
	dfs(r, c, bub->getOption());
	int cnt = 0;
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
			if (visited[r][c])
				cnt++;
	if (cnt < 3)
		return ret;
	for (int r = 1; r <= GAME_ROW_COUNT - 1; r++)
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
			if (visited[r][c])
			{
				bubbled[r][c] = false;
				color[r][c] = -1;
				ret.push_back({r, c});
			}
	return ret;
}

// reimplementation of BubbleDrop
std::vector<std::pair<int, int>> Board::BubbleDropRC()
{
	std::vector<std::pair<int, int>> drop_vector;
	srand(time(0));
	std::vector<Bubble> ret;
	memset(visited, false, sizeof(visited));
	dfs(0, 1, -1);
	for (int r = 1; r <= GAME_ROW_COUNT + 1; r++)
		for (int c = 1; c <= GAME_COLUMN_COUNT - 2; c++)
			if (!visited[r][c] && bubbled[r][c])
			{
				bubbled[r][c] = false;
				color[r][c] = -1;
				drop_vector.push_back({r, c});
			}

	return drop_vector;
}

void Board::dfs(int row, int col, int option)
{
	visited[row][col] = true;
	// Odd Row
	if (row % 2)
	{
		for (int j = 0; j < 2; j++)
		{
			if (!isValid2(row + 1, col + dc[j]))
				continue;
			if (!bubbled[row + 1][col + dc[j]])
				continue;
			if (option != -1 && color[row + 1][col + dc[j]] != option)
				continue;
			if (visited[row + 1][col + dc[j]])
				continue;
			dfs(row + 1, col + dc[j], option);
		}
		for (int j = 0; j < 2; j++)
		{
			if (!isValid2(row - 1, col + dc[j]))
				continue;
			if (!bubbled[row - 1][col + dc[j]])
				continue;
			if (option != -1 && color[row - 1][col + dc[j]] != option)
				continue;
			if (visited[row - 1][col + dc[j]] || color[row - 1][col + dc[j]] != option)
				continue;
			dfs(row - 1, col + dc[j], option);
		}
		for (int j = 0; j < 3; j++)
		{
			if (!isValid2(row, col + dc[j]))
				continue;
			if (!bubbled[row][col + dc[j]])
				continue;
			if (option != -1 && color[row][col + dc[j]] != option)
				continue;
			if (visited[row][col + dc[j]])
				continue;
			dfs(row, col + dc[j], option);
		}
	}

	// Even Row
	else
	{
		for (int j = 1; j < 3; j++)
		{
			if (!isValid2(row + 1, col + dc[j]))
				continue;
			if (!bubbled[row + 1][col + dc[j]])
				continue;
			if (option != -1 && color[row + 1][col + dc[j]] != option)
				continue;
			if (visited[row + 1][col + dc[j]])
				continue;
			dfs(row + 1, col + dc[j], option);
		}
		for (int j = 1; j < 3; j++)
		{
			if (!isValid2(row - 1, col + dc[j]))
				continue;
			if (!bubbled[row - 1][col + dc[j]])
				continue;
			if (option != -1 && color[row - 1][col + dc[j]] != option)
				continue;
			if (visited[row - 1][col + dc[j]] || color[row - 1][col + dc[j]] != option)
				continue;
			dfs(row - 1, col + dc[j], option);
		}
		for (int j = 0; j < 3; j++)
		{
			if (!isValid2(row, col + dc[j]))
				continue;
			if (!bubbled[row][col + dc[j]])
				continue;
			if (option != -1 && color[row][col + dc[j]] != option)
				continue;
			if (visited[row][col + dc[j]])
				continue;
			dfs(row, col + dc[j], option);
		}
	}
}

void Board::cheatClear(){
	for (int i = 0 ; i < GAME_COLUMN_COUNT ; i++){
		bubbled[1][i] = false;
	}
}

void Board::gameOver(){
	for (int i = 0 ; i < GAME_COLUMN_COUNT ; i++){
		bubbled[1][i] = false;
	}
}

bool Board::checkGameOver(int row_down) {
	for (int i = 0 ; i < GAME_COLUMN_COUNT ; i++){
		if (bubbled[GAME_ROW_DEADLINE - row_down][i]) return true;
	}
	return false;
}
