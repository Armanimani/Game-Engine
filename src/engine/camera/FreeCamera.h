#pragma once
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera(const std::string& name, const CameraFrustum& frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : Camera(name, frustum, type, position, direction) {}

	inline virtual void translate(const glm::vec2& value) override { moveRight(value.x); moveUp(value.y); }
	inline virtual void moveForward(const GLfloat& value) override { position += direction * value; }
	inline virtual void moveRight(const GLfloat& value) override { position += right * value; }
	inline virtual void moveUp(const GLfloat& value) override { position += up * value; }
	virtual void rotateForward(const GLfloat& value) override;
	virtual void rotateRight(const GLfloat& value) override;
	virtual void rotateUp(const GLfloat& value) override;
	virtual void orbit(const glm::vec2& value) override;
	inline virtual void zoom(const GLfloat& value) override { moveForward(value); }
};