#include "Entity.h"

void Entity::load()
{
	model->getMesh()->load();
}

void Entity::render()
{
	model->getMaterial->getShader()->render(model);
}
