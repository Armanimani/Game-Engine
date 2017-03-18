#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

//#include "Camera.h"
//
//void Camera::translate(const glm::vec2 & amount)
//{
//	glm::vec3 newDeltaPosition = rightDirection * amount.x + upDirection * amount.y;
//	position += newDeltaPosition;
//	target += newDeltaPosition;
//}
//
//void Camera::zoom(const GLfloat & amount)
//{
//	glm::vec3 viewDirection = glm::normalize(position - target);
//	glm::vec3 zoomIncreament = -viewDirection * amount;
//
//	if ((position - target).x * (position - target).x + (position - target).y * (position - target).y
//		+ (position - target).z * (position - target).z > zoomIncreament.x * zoomIncreament.x + zoomIncreament.y * zoomIncreament.y
//		+ zoomIncreament.z * zoomIncreament.z || amount < 0) {
//		position += zoomIncreament;
//	}
//}
//
//void Camera::rotateX(const GLfloat & amount)
//{
//	glm::vec4 distance = glm::vec4(position - target, 1.0f);
//	glm::mat4 rotation = glm::rotate(glm::radians(-amount), rightDirection);
//	glm::vec4 newDistance = rotation * distance;
//	position = target + glm::vec3(newDistance);
//	upDirection = glm::cross(rightDirection, glm::normalize(glm::vec3(-newDistance)));
//	upDirection = normalize(upDirection);
//}
//
//void Camera::rotateY(const GLfloat & amount)
//{
//	glm::vec4 distance = glm::vec4(position - target, 1.0f);
//	glm::mat4 rotation = glm:: rotate(glm::radians(-amount), upDirection);
//	glm::vec4 newDistance = rotation * distance;
//	position = target + glm::vec3(newDistance);
//	rightDirection = glm::cross(upDirection, glm::normalize(glm::vec3(newDistance)));
//	rightDirection = normalize(rightDirection);
//}
//
//void Camera::rotateZ(const GLfloat & amount)
//{
//	glm::vec4 distance = glm::vec4(position - target, 1.0f);
//	glm::mat4 rotation = glm::rotate(glm::radians(-amount), viewDirection);
//	rightDirection = glm::vec3(rotation * glm::vec4(rightDirection, 1.0));
//	rightDirection = normalize(rightDirection);
//	upDirection = glm::vec3(rotation * glm::vec4(upDirection, 1.0));
//	upDirection = normalize(upDirection);
//}
//
//void Camera::orbit(const glm::vec2 & amount)
//{
//	rotateX(amount.x);
//	rotateY(amount.y);
//}

void Camera::setCameraProjectionType(const CameraProjectionType & t)
{
	projectionType = t;
	updateProjectionMatrix();
}

void Camera::updateMatrix()
{
	updateProjectionMatrix();
}

void Camera::updateProjectionMatrix()
{
	if (projectionType == CameraProjectionType::prespective)
	{
		projectionMatrix = glm::perspective(glm::radians(frustum.FOV), static_cast<GLfloat>(*frustum.viewportWidth) / static_cast<GLfloat>(*frustum.viewportHeight) , frustum.nearPlane, frustum.farPlane);
	}
	else if (projectionType == CameraProjectionType::orthogonal)
	{
		projectionMatrix = glm::ortho(static_cast<unsigned short int>(0), *frustum.viewportWidth, static_cast<unsigned short int> (0), *frustum.viewportHeight);
	}
}
