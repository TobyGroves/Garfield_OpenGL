#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <vector>
#include <exception>
#include <memory>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp> 

class ShaderProgram;
class Transform;

class Camera
{
public:
	Camera(std::vector<std::shared_ptr<ShaderProgram>> _shaders, Transform * _transform);

	void update();

	Transform * transform;

	glm::vec3 camPos;
	
	std::vector<std::shared_ptr<ShaderProgram>> shaders;


};