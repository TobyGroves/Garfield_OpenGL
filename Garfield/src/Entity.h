#include <string>

class ShaderProgram;
class Transform;
class Texture;
class VertexArray;
class VertexBuffer;
class RenderTexture;

class Entity
{
public:
	Entity(Texture *_texture, VertexArray *_mesh, Transform * _transform, float _shine, ShaderProgram* _shader);

	Transform* transform;

	std::string tag;

	void draw();
	void draw(RenderTexture *renderTexture);

private:
	ShaderProgram *shader;

	Texture *texture;
	
	float shine;

	VertexArray *mesh;

};
