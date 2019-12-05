#pragma once

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include "Settings.h"


static GLuint bgtextureID;


class Texture
{
private:
    /* data */
    GLubyte* bgtextureData;
    int bgtextureWidth, bgtextureHeight;

	FIBITMAP* bitmap32;

    // tweaks
    float translationfV [3];
    float fov;

    double zNear, zFar;

protected:
    // FIBITMAP* createBitMap(char const* filename);

public:
    Texture(char const* filename);
    ~Texture();

    void drawTexture();

    void setTranslationfV(float x, float y, float z = -4.5);
    void setFoV(float _fov);

    void setzNear(double _znear);
    void setzFar(double _zfar);


};
