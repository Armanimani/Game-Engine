#pragma once

#include "Texture.h"

class FontTexture : public Texture
{
public:
	FontTexture(const std::string& name, const std::string& path, const GLuint& width, const GLuint& height) : Texture(name, path, width, height) {}

	virtual void load() override;
	virtual void cleanUp() override;
};