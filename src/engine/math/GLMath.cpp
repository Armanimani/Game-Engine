#include "GLMath.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

const glm::vec3 GLMath::X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GLMath::Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 GLMath::Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

glm::mat4 GLMath::createTransformationMatrix(const glm::vec3 & translation, const glm::vec3 & rotation, const glm::vec3 & scale)
{
	glm::mat4 translationMatrix = glm::translate(translation);

	glm::mat4 rotationMatrix_x = glm::rotate(translationMatrix, glm::radians(rotation.x),X_AXIS);
	glm::mat4 rotationMatrix_y = glm::rotate(rotationMatrix_x, glm::radians(rotation.y), Y_AXIS);
	glm::mat4 rotationMatrix_z = glm::rotate(rotationMatrix_y, glm::radians(rotation.z), Z_AXIS);

	glm::mat4 scaleMatrix = glm::scale(rotationMatrix_z, scale);

	return scaleMatrix;
}
