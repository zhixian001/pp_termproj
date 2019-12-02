#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::setEmission(float r, float g, float b, float a)
{
    this->emission[0] = r;
    this->emission[1] = g;
    this->emission[2] = b;
    this->emission[3] = a;
}

void Material::setAmbient(float r, float g, float b, float a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;
}

void Material::setDiffuse(float r, float g, float b, float a)
{
    this->diffuse[0] = r;
    this->diffuse[1] = g;
    this->diffuse[2] = b;
    this->diffuse[3] = a;
}

void Material::setSpecular(float r, float g, float b, float a)
{
    this->specular[0] = r;
    this->specular[1] = g;
    this->specular[2] = b;
    this->specular[3] = a;
}

void Material::setShininess(float sh)
{
    this->shininess[0] = sh;
}

const float *Material::getEmission() const
{
    return this->emission;
}

const float *Material::getAmbient() const
{
    return this->ambient;
}

const float *Material::getDiffuse() const
{
    return this->diffuse;
}

const float *Material::getSpecular() const
{
    return this->specular;
}

const float *Material::getShininess() const
{
    return this->shininess;
}
