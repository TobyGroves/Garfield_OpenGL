#include <string>
#include <memory>

class ShaderProgram;
class Transform;
class Texture;
class VertexArray;
class VertexBuffer;
class RenderTexture;

class Entity
{
public:
	Entity(Texture *_texture, Texture *_normalMap, VertexArray *_mesh, Transform * _transform, float _shine, std::shared_ptr<ShaderProgram> _shader);

	Transform* transform;

	std::string tag;

	void draw();
	void draw(std::shared_ptr<RenderTexture> rendTex);
	void draw(RenderTexture *renderTexture);

private:
	std::shared_ptr<ShaderProgram> shader;

	Texture *texture;
	Texture *normalMap;
	
	float shine;

	VertexArray *mesh;

};
