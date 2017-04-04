#pragma once
#include "Model.h"
#include "../text/Font.h"

class GUITextModel : public Model
{
public:
	GUITextModel(const std::string& name, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const std::shared_ptr<Font> font) : Model(name, mesh, material), font(font) {}

	inline const std::shared_ptr<Font> getFont() { return font; }

protected:
	std::shared_ptr<Font> font;
};