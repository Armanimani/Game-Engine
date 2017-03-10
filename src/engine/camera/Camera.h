#pragma once
#include "glm\glm.hpp"
#include "glew\GL\glew.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& upDirection) : position(position), target(target), upDirection(upDirection)
	{

	}

	inline const glm::mat4 getViewMatrix() { return glm::lookAt(position, target, upDirection); }

	inline const glm::vec3& getPosition() { return position; }
	inline const glm::vec3& getTarget() { return target; }
	inline const glm::vec3& getUpDirection() { return upDirection; }
	inline const glm::vec3& getRightDirection() { return rightDirection; }
	inline const glm::vec3& getViewDirection() { return viewDirection; }

	inline void setPosition(const glm::vec3& pos) { position = pos; }
	inline void setTraget(const glm::vec3& pos) { target = pos; }
	inline void setUpDirection(const glm::vec3& dir) { upDirection = dir; }
	inline void setRightDirection(const glm::vec3& dir) { rightDirection = dir; }
	inline void setViewDirection(const glm::vec3& dir) { viewDirection = dir; }

	void translate(const glm::vec2& amount);
	void zoom(const GLfloat& amount);
	void rotateX(const GLfloat& amount);
	void rotateY(const GLfloat& amount);
	void rotateZ(const GLfloat& amount);
	void orbit(const glm::vec2& amount);

	virtual void update() {};

protected:
	glm::vec3 position;
	glm::vec3 upDirection;
	glm::vec3 rightDirection;
	glm::vec3 viewDirection;
	glm::vec3 target;

};