#pragma once

#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "Settings.h"

class Texture
{
private:
    /* data */
    GLuint bgtextureID;
    GLubyte* bgtextureData;
    int bgtextureWidth, bgtextureHeight;


    // tweaks
    float translationfV [3];
    float fov;

    double zNear, zFar;

protected:
    FIBITMAP* createBitMap(char const* filename);

public:
    Texture(char const* filename);
    ~Texture();

    void drawTexture();

    void setTranslationfV(float x, float y, float z = -4.5);
    void setFoV(float _fov);

    void setzNear(double _znear);
    void setzFar(double _zfar);

};
