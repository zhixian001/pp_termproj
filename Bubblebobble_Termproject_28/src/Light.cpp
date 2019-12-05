#include "Light.h"

Light::Light(/* args */)
{
}

Light::Light(float x, float y, float z, int L_ID)
{
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
    this->lightID = L_ID;
}

Light::~Light()
{
}

void Light::setAmbient(float r, float g, float b, float a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;
}

void Light::setDiffuse(float r, float g, float b, float a)
{
    this->diffuse[0] = r;
    this->diffuse[1] = g;
    this->diffuse[2] = b;
    this->diffuse[3] = a;
}

void Light::setSpecular(float r, float g, float b, float a)
{
    this->specular[0] = r;
    this->specular[1] = g;
    this->specular[2] = b;
    this->specular[3] = a;
}

void Light::draw() const
{
    glEnable(this->lightID);
    glLightfv(this->lightID, GL_AMBIENT, this->ambient);
    glLightfv(this->lightID, GL_DIFFUSE, this->diffuse);
    glLightfv(this->lightID, GL_SPECULAR, this->specular);
    glLightfv(this->lightID, GL_POSITION, this->pos);
    // glDisable(this->lightID);
}
