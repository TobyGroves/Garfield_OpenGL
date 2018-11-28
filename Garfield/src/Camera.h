#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <vector>
#include <exception>

class ShaderProgram;
class Transform;

class Camera
{
public:
	Camera(std::vector<ShaderProgram*> _shaders, Transform * _transform);

	void update();

	Transform * transform;

	std::vector<ShaderProgram *> shaders;


};