#pragma once

#include "ViewportLayout.h"

class ViewportLayoutDefault : public ViewportLayout
{
public:
	ViewportLayoutDefault(const std::shared_ptr<WindowSettings> settings) : ViewportLayout(settings, ViewportLayoutType::default) {}
	virtual void initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams) override;
	virtual void updateLayout(std::vector<std::shared_ptr<Viewport>>& map) override;
};