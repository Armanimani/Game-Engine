#pragma once

#include "ViewportLayout.h"

class ViewportLayoutH1V2 : public ViewportLayout
{
public:
	ViewportLayoutH1V2(const std::shared_ptr<WindowSettings> settings, const GLfloat& cutY) : ViewportLayout(settings, ViewportLayoutType::H2V1), cutY(cutY) {}
	virtual void initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams) override;
	virtual void updateLayout(std::vector<std::shared_ptr<Viewport>>& map) override;

protected:
	GLfloat cutY;
};