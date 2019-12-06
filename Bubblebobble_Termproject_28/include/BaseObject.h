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
    Emerald
} MaterialPreset;

class BaseObject
{
private:
    /* 프리셋 material 적용 함수 */
    void applyPreset(int preset_number);

protected:
    Material mtl;
    /* material 설정하는 함수. 상속된 클래스에서만 사용 가능 */
    void drawMaterial() const;

public:
    BaseObject();
    BaseObject(int preset);
    BaseObject(MaterialPreset preset);
    virtual ~BaseObject();

    void drawMaterialOnly() const;

    // virtual void draw() const;
};
