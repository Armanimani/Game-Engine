#include "Scene3.h"
#include "../../engine/viewport/layout/ViewportLayoutH1V2.h"

void Scene3::setViewports(const std::shared_ptr<WindowSettings> windowSettings)
{
	std::shared_ptr<ViewportLayoutH1V2> layout = std::make_shared<ViewportLayoutH1V2>(windowSettings, 0.5);
	std::vector<std::shared_ptr<Camera>> cams;
	cams.push_back(manager->cameraManager.getCamera("mainCamera"));
	cams.push_back(manager->cameraManager.getCamera("orthoCam"));
	viewportManager->setLayout(layout, cams);
}
