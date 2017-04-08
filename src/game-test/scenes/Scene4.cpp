#include "Scene4.h"
#include "../../engine/viewport/layout/ViewportLayoutH2V2.h"

void Scene4::setViewports()
{
	std::shared_ptr<ViewportLayoutH2V2> layout = std::make_shared<ViewportLayoutH2V2>(windowSettings, 0.5, 0.5);
	std::vector<std::shared_ptr<Camera>> cams;
	cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	cams.push_back(manager->cameraManager.getCamera("arcBallCam"));
	cams.push_back(manager->cameraManager.getCamera("orthoCam2D"));
	viewportManager->setLayout(layout, cams);
}
