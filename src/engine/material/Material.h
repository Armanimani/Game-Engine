#pragma once
#include "../shader/BasicShader.h"
#include <memory>

class Material
{
public:
	Material(std::shared_ptr<Shader> shader) : shader(shader) {}
	inline const std::shared_ptr<Shader>& getShader() { return shader; }
protected:
	std::shared_ptr<Shader> shader;
};