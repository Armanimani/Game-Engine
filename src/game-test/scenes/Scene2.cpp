#include "Scene2.h"
#include "../../engine/viewport/layout/ViewportLayoutH2V1.h"

void Scene2::setViewports(const std::shared_ptr<WindowSettings> windowSettings)
{
	std::shared_ptr<ViewportLayoutH2V1> layout = std::make_shared<ViewportLayoutH2V1>(windowSettings, 0.5);
	std::vector<std::shared_ptr<Camera>> cams;
	cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	viewportManager->setLayout(layout, cams);
}
