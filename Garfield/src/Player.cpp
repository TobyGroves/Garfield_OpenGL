#define _USE_MATH_DEFINES
#include "Player.h"
#include "Camera.h"
#include "Transform.h"
#include "Entity.h"
#include <iostream>
#include<math.h>





Player::Player(Entity * _PlayerEntity, Transform * _transform, float _movementSpeed,float _rotationSpeed,Camera * _camera)
{
	PlayerEntity = _PlayerEntity;
	transform = _transform;
	movementSpeed = _movementSpeed;
	rotationSpeed = _rotationSpeed;
	transform = new Transform(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	camera = _camera;
	//camXrot = 0.0f;

	camXrot = 0.0f;
	camYrot = 0.0f;

	mouseSpeed = 0.005f;

	oldMouseX = 0;
	oldMouseY = 0;



}

void Player::Update()
{
	////////// MOVING  //////////////

	glm::mat4 t(1.0f);

	float currentrot = transform->getRotation().y;

	t = glm::rotate(t, glm::radians(currentrot), glm::vec3(0, 1, 0));

	t = glm::translate(t, glm::vec3(0, 0, 1));

	fwd = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	fwd = -glm::normalize(fwd);

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
		movtemp = transform->getPosition();
		movtemp -= movementSpeed * right;
		transform->setPosition(movtemp);
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
		//move right
		movtemp = transform->getPosition();
		movtemp += movementSpeed * right;
		transform->setPosition(movtemp);
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		movtemp = transform->getPosition();
		movtemp -= movementSpeed * up * 0.5f;
		transform->setPosition(movtemp);
	}
	if (state[SDL_SCANCODE_UP])
	{
		movtemp = transform->getPosition();
		movtemp += movementSpeed * up * 0.5f;
		transform->setPosition(movtemp);
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		movtemp = transform->getRotation();
		movtemp += movementSpeed * up * 2.0f;
		transform->setRotation(movtemp);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		movtemp = transform->getRotation();
		movtemp -= movementSpeed * up * 2.0f;
		transform->setRotation(movtemp);
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		std::cout << "Position :" << PlayerEntity->transform->getPosition().x << ", " << PlayerEntity->transform->getPosition().y << ", " << PlayerEntity->transform->getPosition().z << std::endl;
		std::cout << "Rotation :" << PlayerEntity->transform->getRotation().x << ", " << PlayerEntity->transform->getRotation().y << ", " << PlayerEntity->transform->getRotation().z << std::endl;
	}


	



	PlayerEntity->transform->setPosition(transform->getPosition());
	PlayerEntity->transform->setRotation(transform->getRotation());
	PlayerEntity->transform->setScale(transform->getScale());


	camera->transform->setRotation(PlayerEntity->transform->getRotation());
	camera->transform->setPosition(PlayerEntity->transform->getPosition());
	camera->transform->setScale(PlayerEntity->transform->getScale());


	////////////////////////////////////////////////////////////////

}
