#pragma once

#include "TargetCamera.h"

class ArcBallCamera : public TargetCamera
{
public:
	ArcBallCamera(const std::string& name, const CameraFrustum& frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& target) : TargetCamera(name, frustum, type, position, target) {}
};