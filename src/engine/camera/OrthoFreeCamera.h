#pragma once

#include "FreeCamera.h"

class OrthoFreeCamera : public FreeCamera
{
public:
	OrthoFreeCamera(const std::string& name, CameraFrustum frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : FreeCamera(name, frustum, type, position, direction) 
	{
		this->type = CameraType::orthoFree;
		aspectRatio = static_cast<GLfloat>(*frustum.viewportWidth) / static_cast<GLfloat>(*frustum.viewportHeight);
		this->frustum.viewLeft *= aspectRatio;
		this->frustum.viewRight *= aspectRatio;
	};

	//TODO fix aspectRatio when the window changed!

	virtual void moveForward(const GLfloat& value) override final;

protected:
	GLfloat scale = 0.0;
	virtual void updateProjectionMatrix() override;
private:
	GLfloat aspectRatio;
};