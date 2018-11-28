#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Transform 
{
public:
	Transform(glm::vec3 _position,glm::vec3 _rotation, glm::vec3 _scale);


	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();

	void setPosition(glm::vec3 _position);
	void setRotation(glm::vec3 _rotation);
	void setScale(glm::vec3 _scale);

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

};
