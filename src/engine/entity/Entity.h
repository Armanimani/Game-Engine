#pragma once

#include "../model/Model.h"
#include <glm\glm.hpp>


class Entity
{
public:
	Entity(const std::string& name,  std::shared_ptr<Model> model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) 
		: name(name), model(model), position(position), rotation(rotation), scale(scale) {}
	
	inline const std::string& getName() { return name; }
	inline const std::shared_ptr<Model> getModel() { return model; }

	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getRotation() { return rotation; }
	inline glm::vec3 getScale() { return scale; }

	inline void translateEntity(const glm::vec3& amount) { position += amount; }
	inline void rotateEntity(const glm::vec3& amount) { rotation += amount; }
	inline void scaleEntity (const glm::vec3& amount) { scale *= amount; }

	inline void setHidden(const GLboolean& state = true) { hidden = state; }
	inline const GLboolean& getHidden() { return hidden; }

protected:
	std::string name;
	std::shared_ptr<Model> model;
	glm::vec3 position {0.0f, 0.0f, 0.0f};
	glm::vec3 rotation {0.0f, 0.0f, 0.0f};
	glm::vec3 scale {0.0f, 0.0f, 0.0f};
	GLboolean hidden = false;
};