#include "ViewportManager.h"
#include <iostream>

void ViewportManager::prepare()
{
	for (std::size_t i = 0; i != map.size(); ++i)
	{
		std::shared_ptr<Viewport> viewport = map[i];
		std::shared_ptr<RectangleShape> rect = viewport->getRect();
		std::shared_ptr<Camera> cam = viewport->getCamera();
		CameraFrustum frustum = cam->getFrustum();
		frustum.aspectRatio = rect->getAspectRatio();
		cam->setFrustum(frustum);
	}
}

std::shared_ptr<Camera> ViewportManager::findCamera(const GLuint & x, const GLuint & y)
{
	for (std::size_t i = 0; i != map.size(); ++i)
	{
		if (map[i]->getRect()->isInside(x, layout->getWindowResolutionY() - y))
		{
			return map[i]->getCamera();
		}
	}
	return map[0]->getCamera();
}
