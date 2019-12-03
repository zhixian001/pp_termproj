#pragma once

// #include <ctime>
#include <GL/glut.h>
#include <ctime>
#include "Settings.h"

#ifndef GAME_TIMEOUT
#define GAME_TIMEOUT 5000.0
#endif

#ifndef TIME_BAR_WIDTH
#define TIME_BAR_WIDTH 100.0
#endif

class TimeBar
{
public:
    TimeBar();
    // ~TimeBar();

    // bool progressTime();
    void timeTicking();
    void draw() const;
    void reset();
    int getTime();

private:
    std::clock_t base_timer;
    float colored_width;
    int t;
    float pos2d[2];
};