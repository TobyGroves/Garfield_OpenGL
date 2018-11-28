#include "Player.h"
#include "Camera.h"
#include "Transform.h"

#include <iostream>





Player::Player(Camera * _camera, Transform * _transform, float _movementSpeed)
{
	camera = _camera;
	transform = _transform;
	movementSpeed = _movementSpeed;
	Transform * transform = new Transform(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

}

void Player::Update()
{
	////////// MOVING  //////////////

	//including Psudeo player 

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
		glm::vec3 playerPos = transform->getPosition();

		std::cout << "Forward" << std::endl;

		transform->setPosition(playerPos - (fwd * movementSpeed));
	}
	if (state[SDL_SCANCODE_A])
	{
		glm::vec3 playerPos = transform->getPosition();

		std::cout << "Left" << std::endl;

		transform->setPosition(playerPos -(right * movementSpeed));
	}
	if (state[SDL_SCANCODE_S])
	{
		glm::vec3 playerPos = transform->getPosition();

		std::cout << "Right" << std::endl;

		transform->setPosition(playerPos + (fwd * movementSpeed));
	}
	if (state[SDL_SCANCODE_D])
	{
		glm::vec3 playerPos = transform->getPosition();

		std::cout << "Backward" << std::endl;

		transform->setPosition(playerPos + (right * movementSpeed));
	}


	camera->transform->setPosition(transform->getPosition());
	camera->transform->setRotation(transform->getRotation());
	camera->transform->setScale(transform->getScale());



	//Rotation 



	////////////////////////////////////////////////////////////////

}
