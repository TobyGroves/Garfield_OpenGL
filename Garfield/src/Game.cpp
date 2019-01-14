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

int windowWidth = 1800;
int windowHeight = 1000;

Game::Game()
{
	rune0Found = false;
	rune1Found = false;
	runeActive = 0;

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

	shaderSetup();
	
	postProcessingSetup();




	//create camera
	mainCamera = new Camera(shaders, new Transform(glm::vec3(5.703, 10.0f, -5.0f), glm::vec3(0.0f, 0, 0), glm::vec3(1, 1, 1)));


	time = std::shared_ptr<Time>(new Time());
	
	entitysSetup();

	
	//grass ?
	
	//blows in the wind maybe 
	
	// gui 

	GUI.push_back(std::shared_ptr <GUIEntity>(new GUIEntity(new Texture("../assets/pattern1.png"), new VertexArray("../assets/plane.obj"), 
		new Transform(glm::vec3(1800/2, 1000/2, 0), glm::vec3(0, 0, 0), glm::vec3(1800, 1000, 1)), orthoShad)));
	GUI.push_back(std::shared_ptr <GUIEntity>(new GUIEntity(new Texture("../assets/pattern2.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(1800 / 2, 1000 / 2, 0), glm::vec3(0, 0, 0), glm::vec3(1800, 1000, 1)), orthoShad)));
	
	// create player
	player = new Player(entities.at(1), new Transform(glm::vec3(25.0f, 6.0f, -3.7f), glm::vec3(0, 90, 0), glm::vec3(3, 3, 3)), 0.1f,0.07f,mainCamera);

	
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
				(float)windowWidth / (float)windowHeight, 0.1f, 1000.f));
		}

		// Call camera update 
		player->Update();
		mainCamera->update();

		//GAME HERE //

		gameLoop();
		//draw everything
		drawEverythingRendTex();

		glClearColor(135.0f, 206.0f, 235.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawWithPostPro();
		

		SDL_GL_SwapWindow(window);

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
	glm::vec3 runePositions[2];
	runePositions[0] =glm::vec3(10.24, 3, 0.5207);
	runePositions[1] = glm::vec3(6.38437, 2.299, 12.7987);
	glm::vec3 runeDirections[2];
	runeDirections[0]=glm::vec3(0, 65.4, 0);
	runeDirections[1] = glm::vec3(0, 56.6004, 0);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	/*if (state[SDL_SCANCODE_KP_8])
	{
		//forward
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z+0.1));
	}
	if (state[SDL_SCANCODE_KP_4])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x - 0.1, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_2])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z - 0.1));
	}
	if (state[SDL_SCANCODE_KP_6])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x + 0.1, entities[2]->transform->getPosition().y, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_7])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x , entities[2]->transform->getPosition().y + 0.1, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_9])
	{
		entities[2]->transform->setPosition(glm::vec3(entities[2]->transform->getPosition().x , entities[2]->transform->getPosition().y - 0.1, entities[2]->transform->getPosition().z));
	}
	if (state[SDL_SCANCODE_KP_1])
	{
		//rotate
		entities[2]->transform->setRotation(glm::vec3(entities[2]->transform->getRotation().x, entities[2]->transform->getRotation().y - 1, entities[2]->transform->getRotation().z));
	}
	if (state[SDL_SCANCODE_KP_3])
	{
		entities[2]->transform->setRotation(glm::vec3(entities[2]->transform->getRotation().x, entities[2]->transform->getRotation().y + 1, entities[2]->transform->getRotation().z));
	}*/
	/*if (state[SDL_SCANCODE_KP_5])
	{
		//print pos
		std::cout << "entpos" << std::endl;
		std::cout << "pos : " << entities[2]->transform->getPosition().x << "," << entities[2]->transform->getPosition().y << "," << entities[2]->transform->getPosition().z << std::endl;
		std::cout << "rot : " << entities[2]->transform->getRotation().x << "," << entities[2]->transform->getRotation().y << "," << entities[2]->transform->getRotation().z << std::endl;
	}*/

	if (state[SDL_SCANCODE_Q])
	{
		runeActive = 1;
	}
	if (state[SDL_SCANCODE_E])
	{
		runeActive = 0;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		if (glm::distance(glm::vec3(player->transform->getPosition()), runePositions[runeActive]) < 3)
		{
			if (glm::distance(glm::vec3(player->transform->getRotation()), runeDirections[runeActive]) < 15)
			{
				if (runeActive == 1 && !rune1Found)
				{
					std::cout << "Yeah you've got time! You found Mr incredible Congratz!" << std::endl;
					rune1Found = true;
				}
				if (runeActive == 0 && !rune0Found)
				{
					std::cout << "Well Done! You found the spikey houses!" << std::endl;
					rune0Found = true;
				}
			}
		}
	}
}

void Game::shaderSetup()
{
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/light.vert", "../shaders/light.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/lightspecdiff.vert", "../shaders/lightspecdiff.frag")));
	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/lightsdnorm.vert", "../shaders/lightsdnorm.frag")));

	orthoShad = std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/matrix.vert", "../shaders/simple.frag"));

	shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/water.vert", "../shaders/water.frag")));
	//shaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../water.vert", "../lightspecdiff.frag")));
}

void Game::postProcessingSetup()
{

	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/lightkeypass.vert", "../shaders/lightkeypass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/blur.vert", "../shaders/blur.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/mergepass.vert", "../shaders/mergepass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../shaders/nullpass.vert", "../shaders/nullpass.frag")));

	rendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	lightkeyRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blurRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur2RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur3RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	mergeRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));

}

void Game::entitysSetup() 
{
	//create entities

	entities.push_back(new Entity(new Texture("../assets/islandhighres.png"), new Texture("../assets/islandhighres.png"), new VertexArray("../assets/island.obj"),
		new Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(270, 0, 0), glm::vec3(50.0, 50.0, 50.0)), 0.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/default.png"), new Texture("../assets/default.png"), new VertexArray("../assets/cube.obj"),
		new Transform(glm::vec3(5.703, 10.0f, -5.0f), glm::vec3(0, 0, 0), glm::vec3(4, 4, 4)), 24.0f, shaders.at(3), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_rt.png"), new Texture("../skybox/miramar_rt.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(-100, 20, 0), glm::vec3(0, 90, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_lf.png"), new Texture("../skybox/miramar_lf.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(100, 20, 0), glm::vec3(0, 270, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_up.png"), new Texture("../skybox/miramar_up.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(0, 120, 0), glm::vec3(90, 180, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_dn.png"), new Texture("../skybox/miramar_dn.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(0, -80, 0), glm::vec3(270, 0, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_bk.png"), new Texture("../skybox/miramar_bk.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(0, 20, 100), glm::vec3(0, 180, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));

	entities.push_back(new Entity(new Texture("../skybox/miramar_ft.png"), new Texture("../skybox/miramar_ft.png"), new VertexArray("../assets/plane.obj"),
		new Transform(glm::vec3(0, 20, -100), glm::vec3(0, 0, 0), glm::vec3(200, 200, 200)), 12.0f, shaders.at(0), time));





	//water
	/*entities.push_back(new Entity(new Texture("../water.png"), new Texture("../water.png"), new VertexArray("../WaterPlane.obj"),
	new Transform(glm::vec3(0, 0.846993, 0), glm::vec3(270, 0, 0), glm::vec3(100, 100, 100)), 24.0f, shaders.at(4), time));*/

	water = std::shared_ptr<Water>(new Water(new Texture("../assets/watertex.png"), new Texture("../assets/watertexnormal.png"), new VertexArray("../assets/WaterPlane.obj"),
		new Transform(glm::vec3(0, 0.846993, 0), glm::vec3(270, 0, 0), glm::vec3(100, 100, 100)), 24.0f, shaders.at(4), time, new Texture("../assets/flowmap.png")));

	//houses and trees and objects

	entities.push_back(new Entity(new Texture("../assets/incredible.png"), new Texture("../assets/incredible.png"), new VertexArray("../assets/incredible.obj"),
		new Transform(glm::vec3(3.81, 1.895, 11.128), glm::vec3(0, 47, 0), glm::vec3(0.0025, 0.0025, 0.0025)), 12.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/bouncyCastle.png"), new Texture("../assets/bouncyCastleNorm.png"), new VertexArray("../assets/bouncyCastle.obj"),
		new Transform(glm::vec3(3.71, 1.795, 11.028), glm::vec3(0, 57, 0), glm::vec3(0.2, 0.2, 0.2)), 21.0f, shaders.at(3), time));

	entities.push_back(new Entity(new Texture("../assets/cargo.png"), new Texture("../assets/cargo.png"), new VertexArray("../assets/cargo.obj"),
		new Transform(glm::vec3(6.41, 1.695, 2.628), glm::vec3(0, -179, 0), glm::vec3(0.5, 0.5, 0.5)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/clank.png"), new Texture("../assets/clank.png"), new VertexArray("../assets/clank.obj"),
		new Transform(glm::vec3(-27.19, -2.705, -7.672), glm::vec3(0, 61, 0), glm::vec3(1, 1, 1)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/tree.png"), new Texture("../assets/tree.png"), new VertexArray("../assets/tree.obj"),
		new Transform(glm::vec3(3.703, 1.795f, -1.672), glm::vec3(0, 336, 0), glm::vec3(0.04, 0.04, 0.04)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/house.png"), new Texture("../assets/house.png"), new VertexArray("../assets/house.obj"),
		new Transform(glm::vec3(3.689f, 1.9f, -2.633), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/house.png"), new Texture("../assets/house.png"), new VertexArray("../assets/house.obj"),
		new Transform(glm::vec3(3.342f, 1.9f, -3.5), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/house.png"), new Texture("../assets/house.png"), new VertexArray("../assets/house.obj"),
		new Transform(glm::vec3(2.912f, 1.9f, -4.408), glm::vec3(0, 90, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));

	entities.push_back(new Entity(new Texture("../assets/house.png"), new Texture("../assets/house.png"), new VertexArray("../assets/house.obj"),
		new Transform(glm::vec3(2.955f, 1.889f, -5.481), glm::vec3(0, 76, 0), glm::vec3(0.01, 0.01, 0.01)), 24.0f, shaders.at(2), time));
}

void Game::drawEverythingRendTex()
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->draw(rendTex);
	}
	water->draw(rendTex);
	glDisable(GL_DEPTH_TEST);
	
	GUI.at(runeActive)->draw(rendTex);
}

void Game::drawWithPostPro()
{
	// postprocessing 



		// TODO make a post processing function
		// make it blur 8 times at minimum

	postShaders.at(0)->setUniform("in_Texture", rendTex);
	postShaders.at(0)->draw(lightkeyRendTex);

	// bluring
	postShaders.at(1)->setUniform("in_Texture", lightkeyRendTex);
	postShaders.at(1)->draw(blurRendTex);

	postShaders.at(1)->setUniform("in_Texture", blurRendTex);
	postShaders.at(1)->draw(blur2RendTex);

	postShaders.at(1)->setUniform("in_Texture", blur2RendTex);
	postShaders.at(1)->draw(blur3RendTex);

	// finished bluring

	postShaders.at(2)->setUniform("in_TextureA", rendTex);
	postShaders.at(2)->setUniform("in_TextureB", blur3RendTex);
	postShaders.at(2)->draw(mergeRendTex);

	//draw to screen

	postShaders.at(3)->setViewport(glm::vec4(0, 0, windowWidth, windowHeight));
	//postShaders.at(3)->setUniform("in_Texture", mergeRendTex);

	postShaders.at(3)->setUniform("in_Texture", rendTex);

	//postShaders.at(3)->setUniform("in_Texture", lightkeyRendTex);
	postShaders.at(3)->draw();
}