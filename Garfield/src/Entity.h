#include <string>
#include <memory>
#include "Time.h"

class ShaderProgram;
class Transform;
class Texture;
class VertexArray;
class VertexBuffer;
class RenderTexture;

class Entity
{
public:
	Entity(Texture *_texture, Texture *_normalMap, VertexArray *_mesh, Transform * _transform, float _shine, std::shared_ptr<ShaderProgram> _shader, std::shared_ptr<Time> _time);

	Transform* transform;

	std::string tag;

	void draw();
	void draw(std::shared_ptr<RenderTexture> rendTex);
	void draw(RenderTexture *renderTexture);
	VertexArray *mesh;
private:
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Time> time;

	Texture *texture;
	Texture *normalMap;
	
	float shine;


};
