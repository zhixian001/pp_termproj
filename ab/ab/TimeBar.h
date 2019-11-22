#pragma once

#include <ctime>
#include <GL/glut.h>

#include "Settings.h"

#ifndef GAME_TIMEOUT
#define GAME_TIMEOUT 5000.0
#endif

#ifndef TIME_BAR_WIDTH
#define TIME_BAR_WIDTH 100.0
#endif

class TimeBar{
    public:
        TimeBar();
        // ~TimeBar();

        bool progressTime();
        void draw() const;
        void reset();

    private:
        std::clock_t base_timer;
        float colored_width;
        
        float pos2d[2];

};