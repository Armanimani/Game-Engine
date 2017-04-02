#include "ViewportLayoutH2V1.h"

void ViewportLayoutH2V1::initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams)
{
	map.clear();
	std::shared_ptr<RectangleShape> shapeLeft = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x * cutX, 0, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shapeLeft, cams[0]));

	std::shared_ptr<RectangleShape> shapeRight = std::make_shared<RectangleShape>(windowSettings->windowResolution.x * cutX, windowSettings->windowResolution.x, 0, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shapeRight, cams[1]));
}

void ViewportLayoutH2V1::updateLayout(std::vector<std::shared_ptr<Viewport>>& map)
{
	std::shared_ptr<RectangleShape> shapeLeft = map[0]->getRect();
	shapeLeft->setXMin(0);
	shapeLeft->setXMax(windowSettings->windowResolution.x * cutX);
	shapeLeft->setYMin(0);
	shapeLeft->setYMax(windowSettings->windowResolution.y);
	map[0]->setRectangle(shapeLeft);

	std::shared_ptr<RectangleShape> shapeRight = map[1]->getRect();
	shapeRight->setXMin(windowSettings->windowResolution.x * cutX);
	shapeRight->setXMax(windowSettings->windowResolution.x);
	shapeRight->setYMin(0);
	shapeRight->setYMax(windowSettings->windowResolution.y);
	map[1]->setRectangle(shapeRight);
}
