#include "FontTexture.h"
#include <SOIL\SOIL.h>
#include "../debug/Debug.h"

void FontTexture::load()
{
	int w = static_cast<int>(width);
	int h = static_cast<int>(height);

	unsigned char* image = SOIL_load_image(path.c_str(), &w, &h, nullptr, SOIL_LOAD_RGBA);
	if (!image)
	{
		Debug::print("Unable to load texture file!");
		Debug::print(path);
	}
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontTexture::cleanUp()
{
}
