#include"Game.h"
#include "Camera.h"
#include "Player.h"
#include "transform.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <exception>

/*

TODO MAKE TIME WITH DELTA TIME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

*/

float moveAmmount = 0.05;
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

	SDL_Window *window = SDL_CreateWindow("Game Engine",
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
	
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../lightkeypass.vert", "../lightkeypass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../blur.vert", "../blur.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../mergepass.vert", "../mergepass.frag")));
	postShaders.push_back(std::shared_ptr <ShaderProgram>(new ShaderProgram("../nullpass.vert", "../nullpass.frag")));

	rendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	lightkeyRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blurRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur2RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	blur3RendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));
	//mergeRendTex (new RenderTexture(1800, 1000));
	mergeRendTex = std::shared_ptr<RenderTexture>(new RenderTexture(1800, 1000));




	//create camera
	Camera* mainCamera = new Camera(shaders, new Transform(glm::vec3(0, 3, 0.0f), glm::vec3(0.0f, 0, 0), glm::vec3(1, 1, 1)));

	//create entities
	//entities.push_back(new Entity(new Texture("../low_poly_grass2.png"), new VertexArray("../grass_low_poly.obj"), new Transform(glm::vec3(0, 0, -30.0f), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 0.1)), 24.0f, shaders.at(2)));

	entities.push_back(new Entity(new Texture("../re_hall_diffuse.png"), new VertexArray("../re_hall_baked.obj"), new Transform(glm::vec3(2.0f, -2.0f, -16.0f), glm::vec3(0, 90.0f, 0), glm::vec3(1.0, 1.0, 1.0)),0.0f, shaders.at(1)));
	//entities.push_back(new Entity(new Texture("../curuthers_diffuse.png"), new VertexArray("../curuthers.obj"), new Transform(glm::vec3(0, -2.1f, -20.0f), glm::vec3(0, 0, 0), glm::vec3(1.0, 1.0, 1.0)),32.0f, shaders.at(2)));
	entities.push_back(new Entity(new Texture("../garfield.png"), new VertexArray("../garfield.obj"), new Transform(glm::vec3(0, -4, -20.0f), glm::vec3(0, 0, 0), glm::vec3(4, 4, 4)), 24.0f, shaders.at(2)));
	entities.push_back(new Entity(new Texture("../lasagne.png"), new VertexArray("../lasagne.obj"), new Transform(glm::vec3(0, -4, -20.0f), glm::vec3(0, 0, 0), glm::vec3(0.1, 0.1, 0.1)), 16.0f, shaders.at(2)));
	
	// create player
	Player* player = new Player(entities.at(1), new Transform(glm::vec3(0, -4.0f, -20.0f), glm::vec3(0, 0, 0), glm::vec3(4, 4, 4)), 0.21f,10.0f);
	
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

		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		rendTex->clear();


		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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








		for (int i = 0; i < entities.size(); i++)
		{
			entities.at(2)->transform->setRotation(glm::vec3(entities.at(2)->transform->getRotation().x, entities.at(2)->transform->getRotation().y + 0.1, entities.at(2)->transform->getRotation().z));
		}

		//draw house
		for (int i = 0; i < entities.size(); i++)
		{
			entities.at(i)->draw(rendTex);
		}
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//postprocessing 


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
		postShaders.at(3)->setUniform("in_Texture", mergeRendTex);
		postShaders.at(3)->draw();


		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

}