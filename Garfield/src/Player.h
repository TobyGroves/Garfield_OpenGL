#include <glm/glm.hpp>

#include <glm/ext.hpp>

class Transform;
class Camera;
class Entity;

class Player {
public:

	Player(Entity * _PlayerEntity, Transform * _transform, float _movementSpeed,float _rotationSpeed);

	void Update();

	glm::vec3 fwd;
	glm::vec3 right;

private:
	glm::vec3 movtemp;
	Entity * PlayerEntity;
	Camera * camera;
	Transform * transform;
	float movementSpeed;
	float rotationSpeed;
};