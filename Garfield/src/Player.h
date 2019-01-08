#include <glm/glm.hpp>

#include <glm/ext.hpp>

class Transform;
class Camera;
class Entity;

class Player {
public:

	Player(Entity * _PlayerEntity, Transform * _transform, float _movementSpeed,float _rotationSpeed, Camera * _camera);

	void Update();

	glm::vec3 fwd;
	glm::vec3 right;

	Transform * transform;

	float mouseSpeed;

private:
	float camYrot;
	float camXrot;
	glm::vec3 movtemp;
	Entity * PlayerEntity;
	Camera * camera;
	float movementSpeed;
	float rotationSpeed;
	float angle;
	float angleY;
	float radians;
	int oldMouseX;
	int mouseX;
	int oldMouseY;
	int mouseY;

	glm::vec3 up = glm::vec3(0, 1, 0);

};