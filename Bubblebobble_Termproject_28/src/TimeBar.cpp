#include "TimeBar.h"

TimeBar::TimeBar()
{
	base_timer = std::clock();
	colored_width = TIME_BAR_WIDTH;
	t = 300;
	// TODO: change value
	pos2d[0] = 0.0;
	pos2d[1] = 0.0;
}

void TimeBar::draw() const
{
	glPushMatrix();
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(pos2d[0], pos2d[1]);
	glColor3f(1, 0, 0);
	glVertex2f(pos2d[0] + colored_width, pos2d[1]);
	glEnd();
	glPopMatrix();
}

/* If Shot, progressbar reset */
void TimeBar::reset()
{
	t = 300;
	colored_width = TIME_BAR_WIDTH * 1.0 * t / 300;
}

void TimeBar::timeTicking()
{
	t -= 1;
	colored_width = TIME_BAR_WIDTH * 1.0 * t / 300;
}

int TimeBar::getTime()
{
	return t;
}

/* True: timeout, False: otime(k */
// bool TimeBar::progressTime(){
//     colored_width = TIME_BAR_WIDTH * 1.0 * t / 300;
//     if (colored_width < 0){
//         colored_width = TIME_BAR_WIDTH;
//         base_timer = std::clock();
//         return true;
//     }
//     else{
//         return false;
//     }
// }
