#include "Transform.h"



Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
{
	setPosition(_position);
	setRotation(_rotation);
	setScale(_scale);
}


glm::vec3 Transform::getPosition()
{
	return position;
}
glm::vec3 Transform::getRotation()
{
	return rotation;
}
glm::vec3 Transform::getScale()
{
	return scale;
}

void Transform::setPosition(glm::vec3 _position)
{
	position = _position;
}
void Transform::setRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
}
void Transform::setScale(glm::vec3 _scale)
{
	scale = _scale;
}