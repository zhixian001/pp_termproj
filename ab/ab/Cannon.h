#pragma once

#define M_PI 3.14159265358979323846
// 버블 발사 Y 좌표
#ifndef BUBBLE_LAUNCH_Y_COORD
#define BUBBLE_LAUNCH_Y_COORD -270
#endif

#include <cmath>
#include <GL/glut.h>

class Cannon
{
private:
    double head_angle;
    float cylinder_radius, cylinder_halflength;
    int cylinder_slices;
    float cylinder_depth;
    float cone_height;

protected:
    void drawCylinder(GLfloat radius, GLfloat height, GLfloat R, GLfloat G, GLfloat B);

public:
    Cannon();
    ~Cannon();
    void draw();
    void updateAngle(double val);
};
