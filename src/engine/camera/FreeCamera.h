#pragma once
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera(const std::string& name, CameraFrustum frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction) : Camera(name, frustum, type, position), direction(direction)
	{
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		right = glm::normalize(glm::cross(direction, up));
		up = glm::normalize(glm::cross(right, direction));
	}
	
	inline void setDirection(const glm::vec3& value) { direction = value; }
	inline const glm::vec3& getDirection() const { return direction; }

	inline void moveForward(const GLfloat& value) { position += direction * value; }
	inline void moveRight(const GLfloat& value) { position += right * value; }
	inline void moveUp(const GLfloat& value) { position += up * value; }

protected:
	void updateViewMatrix() override;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
};