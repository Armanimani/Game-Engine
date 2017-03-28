#pragma once
#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include "../../scene/SceneManager.h"

class ShaderSharedData
{
public:
	ShaderSharedData() {};

	void init();
	void prepare();

	inline const glm::mat4& getViewMatrix() { return viewMatrix; }
	inline const glm::mat4& getProjectionMatrix() { return projectionMatrix; }

	inline void setSceneManager(const std::shared_ptr<SceneManager> sceneManager) { manager = sceneManager; }

protected:
	std::shared_ptr<SceneManager> manager;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	GLuint matriciesBP = 0;
	GLuint matriciesBuffer;

	GLuint lightSizeBP = 1;
	GLuint lightSizeBuffer;

	GLuint ambientLightBP = 2;
	GLuint ambientLightBuffer;

	GLuint spotLightBP = 3;
	GLuint spotLightBuffer;

	GLuint cameraBP = 4;
	GLuint cameraBuffer;

	struct LightSize
	{
		GLuint ambientLightSize = 0;
		GLuint spotLightSize = 0;
		GLfloat pad1 = 0.0f;
		GLfloat pad2 = 0.0f;
	};

	struct AmbientLights
	{
		glm::vec4 color = glm::vec4(0.0f);
		GLfloat intensity = 0.0f;
		GLfloat pad1 = 0.0f;
		GLfloat pad2 = 0.0f;
		GLfloat pad3 = 0.0f;
	};

	struct SpotLights
	{
		glm::vec4 position = glm::vec4(0.0f);
		glm::vec4 diffuseColor = glm::vec4(0.0f);
		glm::vec4 specularColor = glm::vec4(0.0f);
		GLfloat diffuseIntensity = 0.0f;
		GLfloat specularIntensity = 0.0f;
		GLfloat pad1 = 0.0f;
		GLfloat pad2 = 0.0f;
	};
};