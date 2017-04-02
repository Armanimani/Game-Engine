#include "ViewportLayoutH2V2.h"

void ViewportLayoutH2V2::initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams)
{
	map.clear();
	std::shared_ptr<RectangleShape> shapeTopLeft = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x * cutX, 0, windowSettings->windowResolution.y * cutY);
	map.emplace_back(std::make_shared<Viewport>(shapeTopLeft, cams[0]));

	std::shared_ptr<RectangleShape> shapeTopRight = std::make_shared<RectangleShape>(windowSettings->windowResolution.x * cutX, windowSettings->windowResolution.x, 0, windowSettings->windowResolution.y * cutY);
	map.emplace_back(std::make_shared<Viewport>(shapeTopRight, cams[1]));

	std::shared_ptr<RectangleShape> shapeBottomLeft = std::make_shared<RectangleShape>(0, windowSettings->windowResolution.x * cutX, windowSettings->windowResolution.y * cutY, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shapeBottomLeft, cams[2]));

	std::shared_ptr<RectangleShape> shapeBottomRight = std::make_shared<RectangleShape>(windowSettings->windowResolution.x * cutX, windowSettings->windowResolution.x, windowSettings->windowResolution.y * cutY, windowSettings->windowResolution.y);
	map.emplace_back(std::make_shared<Viewport>(shapeBottomRight, cams[3]));
}

void ViewportLayoutH2V2::updateLayout(std::vector<std::shared_ptr<Viewport>>& map)
{
	std::shared_ptr<RectangleShape> shapeTopLeft = map[0]->getRect();
	shapeTopLeft->setXMin(0);
	shapeTopLeft->setXMax(windowSettings->windowResolution.x * cutX);
	shapeTopLeft->setYMin(0);
	shapeTopLeft->setYMax(windowSettings->windowResolution.y * cutY);
	map[0]->setRectangle(shapeTopLeft);

	std::shared_ptr<RectangleShape> shapeTopRight = map[1]->getRect();
	shapeTopRight->setXMin(windowSettings->windowResolution.x * cutX);
	shapeTopRight->setXMax(windowSettings->windowResolution.x);
	shapeTopRight->setYMin(0);
	shapeTopRight->setYMax(windowSettings->windowResolution.y * cutY);
	map[1]->setRectangle(shapeTopRight);

	std::shared_ptr<RectangleShape> shapeBottomLeft = map[2]->getRect();
	shapeBottomLeft->setXMin(0);
	shapeBottomLeft->setXMax(windowSettings->windowResolution.x * cutX);
	shapeBottomLeft->setYMin(windowSettings->windowResolution.y * cutY);
	shapeBottomLeft->setYMax(windowSettings->windowResolution.y);
	map[2]->setRectangle(shapeBottomLeft);

	std::shared_ptr<RectangleShape> shapeBottomRight = map[3]->getRect();
	shapeBottomRight->setXMin(windowSettings->windowResolution.x * cutX);
	shapeBottomRight->setXMax(windowSettings->windowResolution.x);
	shapeBottomRight->setYMin(windowSettings->windowResolution.y * cutY);
	shapeBottomRight->setYMax(windowSettings->windowResolution.y);
	map[3]->setRectangle(shapeBottomRight);
}
