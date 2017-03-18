#pragma once
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera(const std::string& name, CameraFrustum frustum, const CameraType& type, const CameraProjectionType& pType, const glm::vec3& position) : Camera(name, frustum, type, pType, position) {}
};