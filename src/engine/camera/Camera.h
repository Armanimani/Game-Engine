#pragma once
#include "glm\glm.hpp"
#include "glew\GL\glew.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "CameraType.h"

class Camera
{
public:
	Camera(const CameraType& type, const glm::vec3& position) : type(type), position(position)
	{
		upVector
	}

	inline const glm::mat4 getViewMatrix() { return glm::lookAt(position, target, upVector); }

	inline const glm::vec3& getPosition() { return position; }
	inline const glm::vec3& getupVector() { return upVector; }
	inline const glm::vec3& getrightVector() { return rightVector; }
	inline const glm::vec3& getViewDirection() { return viewVector; }

	inline void setPosition(const glm::vec3& pos) { position = pos; }
	inline void setUpVector(const glm::vec3& dir) { upVector = dir; }
	inline void setRightVector(const glm::vec3& dir) { rightVector = dir; }
	inline void setViewDirection(const glm::vec3& dir) { viewVector = dir; }

	void translate(const glm::vec2& amount);
	void zoom(const GLfloat& amount);
	void rotateX(const GLfloat& amount);
	void rotateY(const GLfloat& amount);
	void rotateZ(const GLfloat& amount);
	void orbit(const glm::vec2& amount);

	virtual void update() {};

protected:
	CameraType type;
	glm::vec3 position;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 viewVector;
};