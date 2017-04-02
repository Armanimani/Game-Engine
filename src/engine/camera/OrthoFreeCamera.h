#pragma once

#include "FreeCamera.h"

class OrthoFreeCamera : public FreeCamera
{
public:
	OrthoFreeCamera(const std::string& name, CameraFrustum frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : FreeCamera(name, frustum, type, position, direction) 
	{
		this->type = CameraType::orthoFree;
	};

	virtual void moveForward(const GLfloat& value) override;

protected:
	GLfloat scale = 0.0;
	virtual void updateProjectionMatrix() override;
};