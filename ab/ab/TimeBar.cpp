#include "TimeBar.h"

TimeBar::TimeBar() {
    base_timer = std::clock();
    colored_width = TIME_BAR_WIDTH;
    // TODO: change value
    pos2d[0] = 0.0;
    pos2d[1] = 0.0;
}

void TimeBar::draw() const {
    glPushMatrix();
    glLineWidth(10);
	// glEnable(GL_LINE_STIPPLE);
	// glLineStipple(3, 0xAAAA);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(pos2d[0], pos2d[1]);
		glColor3f(1, 0, 0);		
		glVertex2f(pos2d[0]+colored_width, pos2d[1]);
	glEnd();
    glPopMatrix();
}

/* If Shot, progressbar reset */
void TimeBar::reset() {
    colored_width = TIME_BAR_WIDTH;
    base_timer = std::clock();
}

/* True: timeout, False: otime(k */
bool TimeBar::progressTime(){
    colored_width = TIME_BAR_WIDTH * (1.0 - (std::clock() - base_timer) / GAME_TIMEOUT);

    if (colored_width < 0){
        colored_width = TIME_BAR_WIDTH;
        base_timer = std::clock();
        return true;
    }
    else{
        return false;
    }
}
