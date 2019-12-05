#include "Texture.h"

Texture::Texture(char const* filename)
{
    // init image
    // init image
	FIBITMAP* bitmap32 = createBitMap(filename);
	bgtextureWidth = FreeImage_GetWidth(bitmap32);
	bgtextureHeight = FreeImage_GetHeight(bitmap32);
	bgtextureData = FreeImage_GetBits(bitmap32);


    translationfV[0] = 0.0;
    translationfV[1] = 0.0;
    translationfV[2] = -4.5;


    fov = 23.0;

	zNear = 0.1;
	zFar = 20;
}

Texture::~Texture()
{
}


FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	if (format == -1) {
		std::cout << "Could not find image: " << filename << " - Aborting." << std::endl;
		exit(-1);
	}

	if (format == FIF_UNKNOWN) {
		std::cout << "Couldn't determine file format - attempting to get from file extension..." << std::endl;
		format = FreeImage_GetFIFFromFilename(filename);

		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Detected image format cannot be read!" << std::endl;
			exit(-1);
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filename);

	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		std::cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << std::endl;
		bitmap32 = bitmap;
	}
	else {
		std::cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << std::endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;
}


void Texture::drawTexture(){
	glPushMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (GLfloat)WIDTH / (GLfloat)(HEIGHT), zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(translationfV[0], translationfV[1], translationfV[2]);
	glEnable(GL_TEXTURE_2D);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &bgtextureID);
	glBindTexture(GL_TEXTURE_2D, bgtextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgtextureWidth, bgtextureHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bgtextureData);

	// glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, bgtextureID);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);glVertex3f(-0.5, -0.5, 0.0);
		glTexCoord2f(0, 1);glVertex3f(-0.5, 0.5, 0.0);
		glTexCoord2f(1, 1);glVertex3f(0.5, 0.5, 0.0);
		glTexCoord2f(1, 0);glVertex3f(0.5, -0.5, 0.0);
	glEnd();

	glDisable(GL_BLEND);
   	glDepthMask(GL_TRUE); 

	glDisable(GL_TEXTURE_2D);
	// glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}


void Texture::setTranslationfV(float x, float y, float z) {
    translationfV[0] = x;
    translationfV[1] = y;
    translationfV[2] = z;
}

void Texture::setFoV(float _fov) {
    this->fov = _fov;
}


void Texture::setzNear(double _znear){
	zNear = _znear;	
}
void Texture::setzFar(double _zfar){
	zFar = _zfar;
}
