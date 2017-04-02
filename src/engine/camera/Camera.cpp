#include "Camera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

void Camera::updateMatrix()
{
	updateProjectionMatrix();
	updateViewMatrix();
}

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(frustum.FOV), frustum.aspectRatio , frustum.nearPlane, frustum.farPlane);
}

void Camera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(position, position + direction, up);
}

