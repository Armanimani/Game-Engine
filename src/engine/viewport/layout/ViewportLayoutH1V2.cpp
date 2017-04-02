#include "ViewportLayoutH1V2.h"

void ViewportLayoutH1V2::initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams)
{
	map.clear();
	std::shared_ptr<RectangleShape> shapeDown = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x, 0, windowSettings->windowResolution.y * cutY);
	map.emplace_back(std::make_shared<Viewport>(shapeDown, cams[0]));

	std::shared_ptr<RectangleShape> shapeUp = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x, windowSettings->windowResolution.y * cutY, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shapeUp, cams[1]));
}

void ViewportLayoutH1V2::updateLayout(std::vector<std::shared_ptr<Viewport>>& map)
{
	std::shared_ptr<RectangleShape> shapeDown = map[0]->getRect();
	shapeDown->setXMin(0);
	shapeDown->setXMax(windowSettings->windowResolution.x);
	shapeDown->setYMin(0);
	shapeDown->setYMax(windowSettings->windowResolution.y * cutY);
	map[0]->setRectangle(shapeDown);

	std::shared_ptr<RectangleShape> shapeUp = map[1]->getRect();
	shapeUp->setXMin(0);
	shapeUp->setXMax(windowSettings->windowResolution.x);
	shapeUp->setYMin(0);
	shapeUp->setYMax(windowSettings->windowResolution.y);
	map[1]->setRectangle(shapeUp);
}
