#pragma once

#include "Texture.h"

class ModelTexture : public Texture
{
public:
	ModelTexture(const std::string& name, const std::string& path, const GLuint& width, const GLuint& height, const GLuint& mlocation) : Texture(name, path, width, height) { location = mlocation; }

	virtual void load() override;
	virtual void cleanUp() override;
};