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
#include "CameraProjectionType.h"

class Camera
{
public:
	Camera(const std::string& name, CameraFrustum& frustum, const CameraType& type, const CameraProjectionType& pType, const glm::vec3& position) : name(name), frustum(frustum), type(type), projectionType(pType), position(position)
	{
		updateProjectionMatrix();
	}

	inline void setName(const std::string& camName) { name = camName; }
	inline const std::string& getName() { return name; }

	inline const CameraType& getCameraType() { return type; }

	void setCameraProjectionType(const CameraProjectionType& t);
	inline const CameraProjectionType& getCameraProjectionType() { return projectionType; }
	
	inline const glm::mat4& getProjectionMatrix() { return projectionMatrix; }

	inline void setActive(const GLboolean& state = true) { active = state; }
	inline const GLboolean& isActive() { return active; }

	inline const glm::vec3& getPosition() { return position; }
	inline const CameraFrustum& getFrostum() { return frustum; }
	//inline const glm::vec3& getupVector() { return upVector; }
	//inline const glm::vec3& getrightVector() { return rightVector; }
	//inline const glm::vec3& getViewDirection() { return viewVector; }

	inline void setPosition(const glm::vec3& pos) { position = pos; }
	inline void setFrustum(const CameraFrustum& f) { frustum = f; }
	//inline void setUpVector(const glm::vec3& dir) { upVector = dir; }
	//inline void setRightVector(const glm::vec3& dir) { rightVector = dir; }
	//inline void setViewDirection(const glm::vec3& dir) { viewVector = dir; }

	inline void setFOV(const GLfloat& value) { frustum.FOV = value; }
	inline void setNearPlane(const GLfloat& value) { frustum.nearPlane = value; }
	inline void setFarPlane(const GLfloat& value) { frustum.farPlane = value; }

	//void translate(const glm::vec2& amount);
	//void zoom(const GLfloat& amount);
	//void rotateX(const GLfloat& amount);
	//void rotateY(const GLfloat& amount);
	//void rotateZ(const GLfloat& amount);
	//void orbit(const glm::vec2& amount);

	virtual void update() {}; //TODO
	void updateMatrix();

protected:
	std::string name;
	CameraType type = CameraType::noType;
	GLboolean active = false;
	CameraProjectionType projectionType = CameraProjectionType::noType;
	glm::vec3 position;
	CameraFrustum frustum;
	glm::mat4 projectionMatrix;

	void updateProjectionMatrix();

	//glm::vec3 upVector;
	//glm::vec3 rightVector;
	//glm::vec3 viewVector;
};