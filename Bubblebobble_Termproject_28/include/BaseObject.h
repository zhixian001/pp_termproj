#pragma once

#include <GL/glut.h>
#include "Material.h"

typedef enum
{
    BlackDefault,
    RedPlastic,
    GreenPlastic,
    BluePlastic,
    YellowPlastic,
    MagentaPlastic,
    Ruby,
    Emerald,
	Gray
} MaterialPreset;

class BaseObject
{

protected:
    Material mtl;
    /* material 설정하는 함수. 상속된 클래스에서만 사용 가능 */
    void drawMaterial() const;

public:
	void applyPreset(int preset_number);
    BaseObject();
    BaseObject(int preset);
    BaseObject(MaterialPreset preset);
    virtual ~BaseObject();

    void drawMaterialOnly() const;

    // virtual void draw() const;
};
