#include "Player.h"
#include "Camera.h"
#include "Transform.h"
#include "Entity.h"
#include <iostream>





Player::Player(Entity * _PlayerEntity, Transform * _transform, float _movementSpeed,float _rotationSpeed)
{
	PlayerEntity = _PlayerEntity;
	transform = _transform;
	movementSpeed = _movementSpeed;
	rotationSpeed = _rotationSpeed;
	Transform * transform = new Transform(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

}

void Player::Update()
{
	////////// MOVING  //////////////

	glm::mat4 t(1.0f);

	float currentrot = transform->getRotation().y;
	
	t = glm::rotate(t, glm::radians(currentrot), glm::vec3(0,1,0));

	t = glm::translate(t, glm::vec3(0, 0, 1));

	fwd = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	fwd = glm::normalize(fwd);

	t = glm::mat4(1.0f);

	t = glm::rotate(t, glm::radians(currentrot), glm::vec3(0, 1, 0));

	t = glm::translate(t, glm::vec3(1, 0, 0));

	right = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	right = glm::normalize(right);


	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W])
	{
		//forward
		movtemp = transform->getPosition();
		movtemp += movementSpeed * fwd;
		transform->setPosition(movtemp);
	}
	if (state[SDL_SCANCODE_A])
	{
		//rotate left
		movtemp = transform->getRotation();
		movtemp = glm::vec3(movtemp.x, movtemp.y + rotationSpeed, movtemp.z);
		transform->setRotation(movtemp);
	}
	if (state[SDL_SCANCODE_S])
	{
		// backward
		movtemp = transform->getPosition();
		movtemp -= movementSpeed * fwd;
		transform->setPosition(movtemp);
	}
	if (state[SDL_SCANCODE_D])
	{
		//Rotate right
		movtemp = transform->getRotation();
		movtemp = glm::vec3(movtemp.x, movtemp.y - rotationSpeed, movtemp.z);
		transform->setRotation(movtemp);
	}


	PlayerEntity->transform->setPosition(transform->getPosition());
	PlayerEntity->transform->setRotation(transform->getRotation());
	PlayerEntity->transform->setScale(transform->getScale());



	//Rotation 



	////////////////////////////////////////////////////////////////

}
