#include <glm/glm.hpp>

#include <glm/ext.hpp>

class Transform;
class Camera;

class Player {
public:

	Player(Camera * _camera, Transform * _transform, float _movementSpeed);

	void Update();

	glm::vec3 fwd;
	glm::vec3 right;

private:

	Camera * camera;
	Transform * transform;
	float movementSpeed;
};