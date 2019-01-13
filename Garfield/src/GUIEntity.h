#include <string>
#include <memory>

class ShaderProgram;
class Transform;
class Texture;
class VertexArray;
class VertexBuffer;
class RenderTexture;

class GUIEntity
{
public:
	GUIEntity(Texture *_texture, VertexArray *_mesh, Transform * _transform, std::shared_ptr<ShaderProgram>_shader);

	Transform* transform;

	std::string tag;

	void draw();
	void draw(std::shared_ptr<RenderTexture> rendTex);
	void draw(RenderTexture *renderTexture);
	VertexArray *mesh;
private:
	std::shared_ptr<ShaderProgram> shader;

	Texture *texture;
	Texture *normalMap;

	float shine;


};