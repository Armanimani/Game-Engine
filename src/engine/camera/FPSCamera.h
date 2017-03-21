#pragma once
#include "FreeCamera.h"

class FPSCamera : public FreeCamera
{
public:
	FPSCamera(const std::string& name, const CameraFrustum& frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : FreeCamera(name, frustum, type, position, direction) {}

	inline virtual void translate(const glm::vec2& value) override { moveRight(value.x); moveUp(value.y); }
	inline virtual void moveForward(const GLfloat& value) override { position += direction * value; }
	inline virtual void moveRight(const GLfloat& value) override { position += right * value; }
	inline virtual void moveUp(const GLfloat& value) override { position += up * value; }

	virtual void rotateRight(const GLfloat& value) override;

protected:
	GLfloat theta = 0.0;
};