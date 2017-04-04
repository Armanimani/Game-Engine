#pragma once

#include "../Shader.h"
#include "../../model/GUITextModel.h"

class TextShader : public Shader
{
public:
	TextShader(const std::string& name, const ShaderType& type, const std::string& vertexShader, const std::string& fragmentShader) :Shader(name, type, vertexShader, fragmentShader) {}

	virtual void render(const std::shared_ptr<Entity> entity) override {};
	virtual void render(const std::shared_ptr<GUITextModel> model) {};


protected:
	virtual void loadAllToUniform(const std::shared_ptr<GUITextModel> model) {}
};