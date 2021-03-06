#pragma once
#include "glm\glm.hpp"
#include "glew\GL\glew.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "CameraType.h"
#include "CameraFrustum.h"
#include <memory>
#include "../util/vector/USIVec2.h"
#include <string>

class Camera
{
public:
	Camera(const std::string& name, const CameraFrustum& frustum, const CameraType& type, const glm::vec3& position, const glm::vec3& direction = glm::vec3(0.0f, 0.0f, 1.0f)) : name(name), frustum(frustum), type(type), position(position), direction(direction)
	{
		this->direction = glm::normalize(direction);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		right = glm::normalize(glm::cross(direction, up));
		up = glm::normalize(glm::cross(right, direction));
		updateProjectionMatrix();
	}

	inline void setName(const std::string& camName) { name = camName; }
	inline const std::string& getName() { return name; }

	inline const CameraType& getCameraType() { return type; }
	
	inline const glm::mat4& getProjectionMatrix() { return projectionMatrix; }
	inline const glm::mat4& getViewMatrix() { return viewMatrix; }

	inline void setActive(const GLboolean& state = true) { active = state; }
	inline const GLboolean& isActive() { return active; }

	inline const glm::vec3& getPosition() { return position; }
	inline void setPosition(const glm::vec3& pos) { position = pos; }

	inline const CameraFrustum& getFrustum() { return frustum; }
	inline void setFrustum(const CameraFrustum& f) { frustum = f; }

	inline void setDirection(const glm::vec3& value) { direction = value; }
	inline const glm::vec3& getDirection() const { return direction; }

	inline void setFOV(const GLfloat& value) { frustum.FOV = value; }
	inline void setNearPlane(const GLfloat& value) { frustum.nearPlane = value; }
	inline void setFarPlane(const GLfloat& value) { frustum.farPlane = value; }

	virtual void translate(const glm::vec2& value) {};
	virtual void moveForward(const GLfloat& value) {};
	virtual void moveRight(const GLfloat& value) {};
	virtual void moveUp(const GLfloat& value) {};
	virtual void rotateForward(const GLfloat& value) {};
	virtual void rotateRight(const GLfloat& value) {};
	virtual void rotateUp(const GLfloat& value) {};
	virtual void orbit(const glm::vec2& value) {};
	virtual void zoom(const GLfloat& value) {};

	virtual void update() {}; //TODO
	void updateMatrix();

protected:
	std::string name;
	CameraType type = CameraType::noType;
	GLboolean active = false;
	glm::vec3 position;
	CameraFrustum frustum;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;

	virtual void updateProjectionMatrix();
	virtual void updateViewMatrix();
};