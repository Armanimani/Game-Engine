#include "ViewportLayoutDefault.h"

void ViewportLayoutDefault::initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams)
{
	map.clear();
	std::shared_ptr<RectangleShape> shape = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x, 0, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shape, cams[0]));
}

void ViewportLayoutDefault::updateLayout(std::vector<std::shared_ptr<Viewport>>& map)
{
	std::shared_ptr<RectangleShape> shape = map[0]->getRect();
	shape->setXMin(0);
	shape->setXMax(windowSettings->windowResolution.x);
	shape->setYMin(0);
	shape->setYMax(windowSettings->windowResolution.y);
	map[0]->setRectangle(shape);
}


