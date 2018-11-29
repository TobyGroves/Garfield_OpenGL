#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <vector>
#include <exception>
#include <memory>

class ShaderProgram;
class Transform;

class Camera
{
public:
	Camera(std::vector<std::shared_ptr<ShaderProgram>> _shaders, Transform * _transform);

	void update();

	Transform * transform;

	std::vector<std::shared_ptr<ShaderProgram>> shaders;


};