//#pragma once
//#include "Camera.h"
//#include "../entity/Entity.h"
//
//class AttachedCamera : public Camera
//{
//public:
//	AttachedCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& upDirection, std::shared_ptr<Entity> entity) : Camera(position, target, upDirection), entity(entity) 
//	{
//		prevPosition = entity->getPosition();
//	}
//
//	virtual void update() override;
//
//protected:
//	std::shared_ptr<Entity> entity;
//	glm::vec3 prevPosition;
//};
