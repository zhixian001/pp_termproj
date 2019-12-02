#include "BaseObject.h"

void BaseObject::applyPreset(int preset_number)
{
	switch (preset_number)
	{
	case RedPlastic:
		mtl.setAmbient(0.0, 0.0, 0.0, 1.0);
		mtl.setDiffuse(0.5, 0.0, 0.0, 1.0);
		mtl.setSpecular(0.7, 0.6, 0.6, 1.0);
		mtl.setShininess(32.0);
		break;
	case GreenPlastic:
		mtl.setAmbient(0.0, 0.0, 0.0, 1.0);
		mtl.setDiffuse(0.1, 0.35, 0.1, 1.0);
		mtl.setSpecular(0.45, 0.55, 0.45, 1.0);
		mtl.setShininess(32.0);
		break;
	case BluePlastic:
		// TOFIX:
		mtl.setAmbient(0.0, 0.0, 0.0, 1.0);
		mtl.setDiffuse(0.0, 0.0, 0.5, 1.0);
		mtl.setSpecular(0.5, 0.5, 0.7, 1.0);
		mtl.setShininess(32.0);
		break;
	case YellowPlastic:
		mtl.setAmbient(0.0, 0.0, 0.0, 0.8);
		mtl.setDiffuse(0.5, 0.5, 0.0, 1.0);
		mtl.setSpecular(0.6, 0.6, 0.5, 1.0);
		mtl.setShininess(32.0);
		break;
	case Ruby:
		mtl.setAmbient(0.1745, 0.01175, 0.01175, 0.55);
		mtl.setDiffuse(0.61424, 0.04136, 0.04136, 0.55);
		mtl.setSpecular(0.727811, 0.626959, 0.626959, 0.55);
		mtl.setShininess(76.8);
		break;
	case Emerald:
		mtl.setAmbient(0.0215, 0.1745, 0.0215, 0.55);
		mtl.setDiffuse(0.07586, 0.61424, 0.07586, 0.55);
		mtl.setSpecular(0.633, 0.727811, 0.611, 0.55);
		mtl.setShininess(76.8);
		break;
	case MagentaPlastic:
		mtl.setAmbient(0.1, 0.0, 0.2, 0.8);
		mtl.setDiffuse(0.5, 0.0, 0.5, 1.0);
		mtl.setSpecular(0.6, 0.5, 0.6, 1.0);
		mtl.setShininess(32);
		break;
	default:
		break;
	}
}

BaseObject::BaseObject()
{
	this->mtl = Material();
}
BaseObject::BaseObject(int preset)
{
	applyPreset(preset);
}

BaseObject::BaseObject(MaterialPreset preset)
{
	applyPreset((int)preset);
}

BaseObject::~BaseObject()
{
}

void BaseObject::drawMaterial() const
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
}
