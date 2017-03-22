#pragma once

#include "FreeCamera.h"

class TargetCamera : public FreeCamera
{
public:
	TargetCamera(const std::string& name, const CameraFrustum& frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& target) : FreeCamera(name, frustum, type, position, target - position), target(target) {}

	virtual void setTraget(const glm::vec3& t) { target = t; }
	virtual const glm::vec3& getTarget() { return target; }

	inline virtual void translate(const glm::vec2& value) override { moveRight(value.x); moveUp(value.y); }
	virtual void moveForward(const GLfloat& value) override;
	virtual void moveRight(const GLfloat& value) override;
	virtual void moveUp(const GLfloat& value) override;
	virtual void rotateForward(const GLfloat& value) override;
	virtual void rotateRight(const GLfloat& value) override;
	virtual void rotateUp(const GLfloat& value) override;
	virtual void orbit(const glm::vec2& value) override;

	virtual void zoom(const GLfloat& value) override;
protected:
	glm::vec3 target;
};