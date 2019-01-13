#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "Water.h"
#include "GUIEntity.h"
#include "RenderTexture.h"
#include "Camera.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Time.h"

class RenderTexture;
class Texture;

class Game
{

public:
	Player* player = nullptr;
	Camera* mainCamera = nullptr;

	Game();

	std::vector<std::shared_ptr<ShaderProgram>> shaders;
	std::vector<std::shared_ptr<ShaderProgram>> postShaders;
	std::vector<Entity *> entities;
	std::vector<std::shared_ptr<GUIEntity>> GUI;
	std::shared_ptr<RenderTexture> rendTex;
	std::shared_ptr<RenderTexture> lightkeyRendTex;
	std::shared_ptr<RenderTexture> blurRendTex;
	std::shared_ptr<RenderTexture> blur2RendTex;
	std::shared_ptr<RenderTexture> blur3RendTex;
	std::shared_ptr<RenderTexture> mergeRendTex;

	std::shared_ptr<ShaderProgram> orthoShad;

	std::shared_ptr<Water> water;

	std::shared_ptr<Time> time;

	void gameLoop();

};