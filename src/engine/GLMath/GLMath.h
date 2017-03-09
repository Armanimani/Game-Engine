#pragma once
#include <glm\glm.hpp>

class GLMath
{
public:
	static glm::mat4 createTransformationMatrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	//static glm::mat4 createProjectionMatrix(const float& FOV, const float& aspectRatio, const float& farPlane, const float& nearPlane);
protected:
	static const glm::vec3 X_AXIS;
	static const glm::vec3 Y_AXIS;
	static const glm::vec3 Z_AXIS;
};