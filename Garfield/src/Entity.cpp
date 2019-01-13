#include "Entity.h"
#include "Transform.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include <memory>

Entity::Entity(Texture *_texture, Texture *_normalMap ,VertexArray *_mesh, Transform * _transform, float _shine, std::shared_ptr<ShaderProgram>_shader, std::shared_ptr<Time> _time)
{
	texture = _texture;
	normalMap = _normalMap;
	mesh = _mesh;
	transform = _transform;
	shader = _shader;
	shine = _shine;
	time = _time;

}


void Entity::draw(RenderTexture *rendTex)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));
	model = glm::scale(model, transform->getScale());

	shader->setUniform("in_Time", time->time);
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);
	shader->setUniform("in_NormalMap", normalMap);
	shader->setUniform("in_Emissive", glm::vec3(0, 0, 0));
	shader->setUniform("in_Ambient", glm::vec3(0.7, 0.7, 0.7));
	shader->setUniform("in_LightPos", glm::vec3(0, 5.0f, 0.0f));
	shader->setUniform("in_LightColor", glm::vec3(0.6, 0.6, 0.6));
	shader->setUniform("in_shine", shine);

	shader->draw(rendTex, mesh);
}

void Entity::draw(std::shared_ptr<RenderTexture> rendTex)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));
	model = glm::scale(model, transform->getScale());

	shader->setUniform("in_Time", ((float)time->time));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);
	shader->setUniform("in_NormalMap", normalMap);
	shader->setUniform("in_Emissive", glm::vec3(0, 0, 0));
	shader->setUniform("in_Ambient", glm::vec3(0.7, 0.7, 0.7));
	shader->setUniform("in_LightPos", glm::vec3(0, 5.0f, 0.0f));
	shader->setUniform("in_LightColor", glm::vec3(0.6, 0.6, 0.6));
	shader->setUniform("in_shine", shine);

	shader->draw(rendTex.get(), mesh);
}

void Entity::draw()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));
	model = glm::scale(model, transform->getScale());

	shader->setUniform("in_Time", time->time);
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);
	shader->setUniform("in_NormalMap", normalMap);
	shader->setUniform("in_Emissive", glm::vec3(0, 0, 0));
	shader->setUniform("in_Ambient", glm::vec3(0.7, 0.7, 0.7));
	shader->setUniform("in_LightPos", glm::vec3(0, 5.0f, 0.0f));
	shader->setUniform("in_LightColor", glm::vec3(0.6, 0.6, 0.6));
	shader->setUniform("in_shine", shine);

	shader->draw(mesh);
}