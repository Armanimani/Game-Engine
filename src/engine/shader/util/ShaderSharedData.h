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

	inline void setGammaCorrection(const GLfloat& value) { gammaCorrection = value; }
	inline const GLfloat& getGammaCorrection() { return gammaCorrection; }

protected:
	std::shared_ptr<SceneManager> manager;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	GLfloat gammaCorrection = 1.0f/ 2.2f;

	GLuint matriciesBP = 0;
	GLuint matriciesBuffer;

	GLuint lightSizeBP = 1;
	GLuint lightSizeBuffer;

	GLuint ambientLightBP = 2;
	GLuint ambientLightBuffer;

	GLuint pointLightBP = 3;
	GLuint pointLightBuffer;

	GLuint cameraBP = 4;
	GLuint cameraBuffer;

	GLuint gammaCorrectionBP = 5;
	GLuint gammaCorrectionBuffer;

	GLuint directionalLightBP = 6;
	GLuint directionalLightBuffer;

	struct LightSize
	{
		GLuint ambientLightSize = 0;
		GLuint pointLightSize = 0;
		GLuint directionalLightSize = 0;
		GLfloat pad2 = 0.0f;
	};

	struct AmbientLights
	{
		glm::vec4 color = glm::vec4(0.0f);
		glm::vec4 position = glm::vec4(0.0f);
		GLfloat intensity = 0.0f;
		GLfloat attenuation = 0.0f;
		GLfloat pad2 = 0.0f;
		GLfloat pad3 = 0.0f;
	};

	struct PointLights
	{
		glm::vec4 position = glm::vec4(0.0f);
		glm::vec4 diffuseColor = glm::vec4(0.0f);
		glm::vec4 specularColor = glm::vec4(0.0f);
		GLfloat diffuseIntensity = 0.0f;
		GLfloat specularIntensity = 0.0f;
		GLfloat attenuation = 0.0f;
		GLfloat pad2 = 0.0f;
	};

	struct DirectionalLights
	{
		glm::vec4 direction = glm::vec4(0.0f);
		glm::vec4 diffuseColor = glm::vec4(0.0f);
		glm::vec4 specularColor = glm::vec4(0.0f);
		GLfloat diffuseIntensity = 0.0f;
		GLfloat specularIntensity = 0.0f;
		GLfloat pad1 = 0.0f;
		GLfloat pad2 = 0.0f;
	};
};