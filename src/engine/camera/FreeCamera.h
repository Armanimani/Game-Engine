#pragma once
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera(const std::string& name, CameraFrustum frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : Camera(name, frustum, type, position, direction) {}
	
	inline void setDirection(const glm::vec3& value) { direction = value; }
	inline const glm::vec3& getDirection() const { return direction; }

	inline void translate(const glm::vec2& value) override { moveRight(value.x); moveUp(value.y); }
	inline void moveForward(const GLfloat& value) override { position += direction * value; }
	inline void moveRight(const GLfloat& value) override { position += right * value; }
	inline void moveUp(const GLfloat& value) override { position += up * value; }

protected:
	void updateViewMatrix() override;
};