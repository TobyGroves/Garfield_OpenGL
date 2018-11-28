#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "RenderTexture.h"
#include <vector>

class RenderTexture;
class Texture;

class Game
{

public:
	Game();
	VertexArray *hallShape;
	Texture *hallTexture;
	VertexArray *shape;
	Texture *texture;
	std::vector<ShaderProgram *> shaders;
	std::vector<ShaderProgram *> postShaders;
	std::vector<Entity *> entities;
	RenderTexture *rendTex;
	RenderTexture *lightkeyRendTex;
	RenderTexture *blurRendTex;
	RenderTexture *blur2RendTex;
	RenderTexture *blur3RendTex;
	RenderTexture *mergeRendTex;



};