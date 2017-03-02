#pragma once

#include <glm\glm.hpp>
#include<memory>

#include "../mesh/Mesh.h"
#include "../model/Model.h"

class Entity
{
public:
	Entity() {};
	Entity(const std::shared_ptr<Model> model, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : model(model), position(position), rotation(rotation), scale(scale) {}
	
	void load();
	void render();
	inline glm::vec3 getPosition() { return position; }
	inline glm::vec3 getRotation() { return rotation; }
	inline glm::vec3 getScale() { return scale; }

protected:
	std::shared_ptr<Model> model;
	glm::vec3 position {0.0f, 0.0f, 0.0f};
	glm::vec3 rotation {0.0f, 0.0f, 0.0f};
	glm::vec3 scale {0.0f, 0.0f, 0.0f};
};