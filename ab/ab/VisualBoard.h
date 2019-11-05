/**
 * @file VisualBoard.h
 * @author JH Yeom (okyjh12@naver.com)
 * @brief visualization module of Game logic
 * @version 0.1
 * @date 2019-11-02
 * 
 * 소스.cpp 모듈에서 하던 일을 포장 & Board에서 하던 일의 일부 역할 분담
 *  공 발사
 *  공 궤적
 *  공 드랍
 *  공 매칭 및 폭파.
 * 
 * 
 * 
 */

#pragma once

#ifndef BUBBLE_RADIUS
#define BUBBLE_RADIUS 25.0
#endif
#ifndef BUBBLE_LAUNCH_X_COORD
#define BUBBLE_LAUNCH_X_COORD 0
#endif
#ifndef BUBBLE_LAUNCH_Y_COORD
#define BUBBLE_LAUNCH_Y_COORD -270
#endif
#ifndef BUBBLE_NEXT_LAUNCH_X_COORD
#define BUBBLE_NEXT_LAUNCH_X_COORD -150
#endif
#ifndef BUBBLE_NEXT_LAUNCH_Y_COORD
#define BUBBLE_NEXT_LAUNCH_Y_COORD -280
#endif

#ifndef BUBBLE_SPEED_MULTIPLIER
#define BUBBLE_SPEED_MULTIPLIER 20
#endif

#ifndef POINTS_PER_BUBBLE
#define POINTS_PER_BUBBLE 100
#endif


#include <cstdlib>
#include <ctime>
#include <cmath>
#include <deque>
#include "Bubble.h"
#include "Cannon.h"
#include "Board.h"


// 발사대기, 공 날아가는 중, 공이 충돌하고 pop과 drop을 resolution하는 중, pop과 drop을 수행
typedef enum {Ready, ShotFlying, ShotCollide, Pop, Drop} GameStates;

class VisualBoard
{
private:
    std::deque<Bubble*> bubblez;
    Board* board;
    Cannon cannon;
    std::deque<Bubble*>::iterator to_launch;
    std::deque<Bubble*>::iterator next_launch;
    std::deque<Bubble*>::iterator flying_now;
    Bubble* bubble_alias[12][10];
    GameStates game_state;
    std::pair<int, int> collision_pair;
    std::vector<std::pair<int, int>> pop_vector;
    std::vector<std::pair<int, int>> drop_vector;
    std::vector<int> dead_bubble_stack;
    std::pair<int, int> tmp;
    std::pair<double, double> coord_tmp;

    unsigned int score;

protected:
	Bubble* generateBubble();
public:
    VisualBoard();
    ~VisualBoard();
    void draw();
    void levelDown();
    void updateCannonAngle(double theta);
    void launchBubble();
    void stateTransition();

    unsigned int getScore() const;
};