#include "Texture.h"

void Texture::activate()
{
	switch (location)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE2);
		break;
	case 3:
		glActiveTexture(GL_TEXTURE3);
		break;
	case 4:
		glActiveTexture(GL_TEXTURE4);
		break;
	case 5:
		glActiveTexture(GL_TEXTURE5);
		break;
	case 6:
		glActiveTexture(GL_TEXTURE6);
		break;
	case 7:
		glActiveTexture(GL_TEXTURE7);
		break;
	case 8:
		glActiveTexture(GL_TEXTURE8);
		break;
	case 9:
		glActiveTexture(GL_TEXTURE9);
		break;
	case 10:
		glActiveTexture(GL_TEXTURE10);
		break;
	case 11:
		glActiveTexture(GL_TEXTURE11);
		break;
	case 12:
		glActiveTexture(GL_TEXTURE12);
		break;
	case 13:
		glActiveTexture(GL_TEXTURE13);
		break;
	case 14:
		glActiveTexture(GL_TEXTURE14);
		break;
	case 15:
		glActiveTexture(GL_TEXTURE15);
		break;
	case 16:
		glActiveTexture(GL_TEXTURE16);
		break;
	case 17:
		glActiveTexture(GL_TEXTURE17);
		break;
	case 18:
		glActiveTexture(GL_TEXTURE18);
		break;
	case 19:
		glActiveTexture(GL_TEXTURE19);
		break;
	case 20:
		glActiveTexture(GL_TEXTURE20);
		break;
	}
}
