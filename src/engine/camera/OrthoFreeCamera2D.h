#pragma once
#include "OrthoFreeCamera.h"

class OrthoFreeCamera2D : public OrthoFreeCamera
{
public:
	OrthoFreeCamera2D(const std::string& name, CameraFrustum frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : OrthoFreeCamera(name, frustum, type, position, direction) {}
protected:

	virtual void rotateForward(const GLfloat& value) override {};
	virtual void rotateRight(const GLfloat& value) override {};
	virtual void rotateUp(const GLfloat& value) override {};
	virtual void orbit(const glm::vec2& value) override {};

};