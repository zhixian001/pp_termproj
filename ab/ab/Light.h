#pragma once

#include <GL/glut.h>

class Light
{
private:
    /* data */
    int lightID;
    float pos[3];
    float ambient[4];
    float diffuse[4];
    float specular[4];

public:
    Light(/* args */);
    Light(float x, float y, float z, int L_ID);
    ~Light();

    void setAmbient(float r, float g, float b, float a);
    void setDiffuse(float r, float g, float b, float a);
    void setSpecular(float r, float g, float b, float a);
    void draw() const;
};
