#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "RenderTexture.h"
#include <vector>
#include <memory>

class RenderTexture;
class Texture;

class Game
{

public:
	Game();
	std::vector<std::shared_ptr<ShaderProgram>> shaders;
	std::vector<std::shared_ptr<ShaderProgram>> postShaders;
	std::vector<Entity *> entities;
	std::shared_ptr<RenderTexture> rendTex;
	std::shared_ptr<RenderTexture> lightkeyRendTex;
	std::shared_ptr<RenderTexture> blurRendTex;
	std::shared_ptr<RenderTexture> blur2RendTex;
	std::shared_ptr<RenderTexture> blur3RendTex;
	std::shared_ptr<RenderTexture> mergeRendTex;


};