#include"Game.h"
#include "transform.h"
#include "Time.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <exception>
#include <memory>
#include <iostream>

/*

TODO MAKE TIME WITH DELTA TIME !

*/

float moveAmmount = 0.01f;
int windowWidth = 1800;
int windowHeight = 1000;
float Xmov = 0;
float Ymov = 0;

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Garfield Game Engine",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	bool quit = false;
	float angle = 0;
	// create shaders

	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../simple.vert", "../simple.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../light.vert", "../light.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../lightspecdiff.vert", "../lightspecdiff.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../lightsdnorm.vert", "../lightsdnorm.frag")));

	orthoShad = std::shared_ptr <ShaderProgram>(new ShaderProgram("../simple.vert", "../simple.frag"));

	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../water.vert", "../water.frag")));
	
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../lightkeypass.vert", "../lightkeypass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../blur.vert", "../blur.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../mergepass.vert", "../mergepass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../nullpass.vert", "../nullpass.frag")));

	rendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	lightkeyRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blurRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur2RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur3RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	mergeRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));




	//create camera
	mainCamera = new Camera(shaders, new Transform(glm::vec3(0, 3, 0.0f), glm::vec3(0.0f, 0, 0), glm::vec3(1, 1, 1)));


	time = std::shared_ptr<Time>(new Time());
	//create entities
	
	entities.push_back(new Entity(new Texture("../islandhighres.png"), new Texture("../brickwall_normal.png")  , new VertexArray("../island.obj"), new Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(270, 0, 0), glm::vec3(50.0, 50.0, 50.0)),0.0f, shaders.at(2),time));
	
	entities.push_back(new Entity(new Texture("../brickwall.png"), new Texture("../brickwall_normal.png"), new VertexArray("../cube.obj"), new Transform(glm::vec3(0, 3, -20.0f), glm::vec3(90, 0, 0), glm::vec3(4, 4, 4)), 24.0f, shaders.at(3), time));

	//water
	//entities.push_back(new Entity(new Texture("../water.png"), new Texture("../water.png"), new VertexArray("../WaterPlane.obj"), new Transform(glm::vec3(0, 0.846993, 0), glm::vec3(270, 0, 0), glm::vec3(100, 100, 100)), 24.0f, shaders.at(4), time));
	water = std::shared_ptr<Water>(new Water(new Texture("../watertex.png"), new Texture("../watertexnormal.png"), new VertexArray("../WaterPlane.obj"), new Transform(glm::vec3(0, 0.846993, 0), glm::vec3(270, 0, 0), glm::vec3(100, 100, 100)), 24.0f, shaders.at(4), time, new Texture("../flowmap.png")));
	
	//houses and trees
	entities.push_back(new Entity(new Texture("../tree.png"), new Texture("../tree.png"), new VertexArray("../tree.obj"), new Transform(glm::vec3(3.703, 1.795f, -1.672), glm::vec3(0, 336, 0), glm::vec3(0.04, 0.04, 0.04)), 24.0f, shaders.at(2), time));
	entities.push_back(new Entity(new Texture("../house.png"), new Texture("../house.png"), new VertexArray("../house.obj"), new Transform(glm::vec3(3.689f, 1.9f, -2.633), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));
	entities.push_back(new Entity(new Texture("../house.png"), new Texture("../house.png"), new VertexArray("../house.obj"), new Transform(glm::vec3(3.342f, 1.9f, -3.5), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));
	entities.push_back(new Entity(new Texture("../house.png"), new Texture("../house.png"), new VertexArray("../house.obj"), new Transform(glm::vec3(2.912f, 1.9f, -4.408), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));
	entities.push_back(new Entity(new Texture("../house.png"), new Texture("../house.png"), new VertexArray("../house.obj"), new Transform(glm::vec3(2.955f, 1.889f, -5.481), glm::vec3(0, 76, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));
	
	//grass ?
	
	//blows in the wind maybe 
	
	// gui 

	GUI.push_back(std::shared_ptr <GUIEntity>(new GUIEntity(new Texture("../tree.png"), new VertexArray("../cube.obj"), new Transform(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(100, 100, 100)), orthoShad)));


	// create player
	player = new Player(entities.at(1), new Transform(glm::vec3(0, 0.0f, 10.0f), glm::vec3(0, 0, 0), glm::vec3(3, 3, 3)), 0.5f,0.4f,mainCamera);
	
	
	//create time

	time->gameStart();

	// Start the Game Loop
	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		// ultimatly menu thing but atm just quits
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE])
		{
			quit = true;
		}


		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		rendTex->clear();
		glViewport(0, 0, windowWidth, windowHeight);
		glClearColor(135.0f, 206.0f, 235.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		* Draw with perspective projection matrix
		*/
		for (int i = 0; i < shaders.size(); i++)
		{
			shaders.at(i)->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
				(float)windowWidth / (float)windowHeight, 0.1f, 100.f));
		}

		// Call camera update 

		player->Update();
		mainCamera->update();

		//GAME HERE //

		gameLoop();






		
		//draw everything
		for (int i = 0; i < entities.size(); i++)
		{
			entities.at(i)->draw(rendTex);
		}
		water->draw(rendTex);
		glDisable(GL_DEPTH_TEST);
		for (int i = 0; i < GUI.size(); i++)
		{
			GUI.at(i)->draw(rendTex);
		}

		glDisable(GL_DEPTH_TEST);
		glClearColor(135.0f, 206.0f, 235.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//postprocessing 
		// make it blur 8 times at minimum

		postShaders.at(0)->setUniform("in_Texture", rendTex);
		postShaders.at(0)->draw(lightkeyRendTex);

		postShaders.at(1)->setUniform("in_Texture", lightkeyRendTex);
		postShaders.at(1)->draw(blurRendTex);

		postShaders.at(1)->setUniform("in_Texture", blurRendTex);
		postShaders.at(1)->draw(blur2RendTex);

		postShaders.at(1)->setUniform("in_Texture", blur2RendTex);
		postShaders.at(1)->draw(blur3RendTex);

		postShaders.at(2)->setUniform("in_TextureA", rendTex);
		postShaders.at(2)->setUniform("in_TextureB", blur3RendTex);
		postShaders.at(2)->draw(mergeRendTex);

		//draw to screen

		postShaders.at(3)->setViewport(glm::vec4(0, 0, windowWidth, windowHeight));
		//postShaders.at(3)->setUniform("in_Texture", mergeRendTex);
		postShaders.at(3)->setUniform("in_Texture", rendTex);
		postShaders.at(3)->draw();



		SDL_GL_SwapWindow(window);

		std::cout << "time :" << (float)time->time << std::endl;

		time->timeUpdate();

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

}




void Game::gameLoop()
{

	//6 runes 
	//6 positions to stand 
	//6 directions to look at
	int runeActive = 0;
	glm::vec3 runePositions[6];
	runePositions[0] =glm::vec3(9.63, 3, -0.43);
	glm::vec3 runeDirections[6];
	runeDirections[0]=glm::vec3(0, 63, 0);

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_KP_8])
	{
		//forward
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z+0.001));
	}
	if (state[SDL_SCANCODE_KP_4])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x - 0.001, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_2])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z - 0.001));
	}
	if (state[SDL_SCANCODE_KP_6])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x + 0.001, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_7])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x , entities[2]->transform->getPosition().y + 0.001, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_9])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x , entities[2]->transform->getPosition().y - 0.001, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_1])
	{
		//rotate
		entities[2]->transform->setRotation(glm::vec3(entities[2]->transform->getRotation().x, entities[2]->transform->getRotation().y - 1, entities[2]->transform->getRotation().z));
	}
	if (state[SDL_SCANCODE_KP_3])
	{
		entities[2]->transform->setRotation(glm::vec3(entities[2]->transform->getRotation().x, entities[2]->transform->getRotation().y + 1, entities[2]->transform->getRotation().z));
	}
	if (state[SDL_SCANCODE_KP_5])
	{
		//print pos
		std::cout << "entpos" << std::endl;
		std::cout << "pos : " << entities[2]->transform->getPosition().x << "," << entities[2]->transform->getPosition().y << "," << entities[2]->transform->getPosition().z << std::endl;
		std::cout << "rot : " << entities[2]->transform->getRotation().x << "," << entities[2]->transform->getRotation().y << "," << entities[2]->transform->getRotation().z << std::endl;
	}

	if (state[SDL_SCANCODE_Q])
	{
		runeActive --;
		if (runeActive < 0)
		{
			runeActive = 5;
		}
	}
	if (state[SDL_SCANCODE_E])
	{
		runeActive--;
		if (runeActive > 5)
		{
			runeActive = 0;
		}
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		if (glm::distance(glm::vec3(player->transform->getPosition()), runePositions[runeActive]) < 2)
		{
			if (glm::distance(glm::vec3(player->transform->getRotation()), runeDirections[runeActive]) < 25)
			{
				std::cout << "boom" << std::endl;
			}
		}
	}
}