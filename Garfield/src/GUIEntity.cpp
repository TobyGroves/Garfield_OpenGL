#include "GUIEntity.h"
#include "Transform.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include <memory>

GUIEntity::GUIEntity(Texture *_texture, VertexArray *_mesh, Transform * _transform,  std::shared_ptr<ShaderProgram>_shader)
{
	texture = _texture;
	mesh = _mesh;
	transform = _transform;
	shader = _shader;

}


void GUIEntity::draw(RenderTexture *rendTex)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	/*model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));*/
	//model = glm::scale(model, transform->getScale());
	model = glm::scale(model,transform->getScale());


	shader->setUniform("in_Projection", glm::ortho(0.0f, 1800.0f, 0.0f, 1000.0f, 0.0f, 1.0f));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);

	shader->draw(rendTex, mesh);
}

void GUIEntity::draw(std::shared_ptr<RenderTexture> rendTex)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	/*model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));*/
	//model = glm::scale(model, transform->getScale());
	model = glm::scale(model, transform->getScale());

	shader->setUniform("in_Projection", glm::ortho(0.0f, 1800.0f, 0.0f, 1000.0f, 0.0f, 1.0f));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);

	shader->draw(rendTex.get(), mesh);
}

void GUIEntity::draw()
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform->getPosition());
	/*model = glm::rotate(model, glm::radians(transform->getRotation().x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform->getRotation().z), glm::vec3(0, 0, 1));*/
	//model = glm::scale(model, transform->getScale());
	model = glm::scale(model, transform->getScale());

	shader->setUniform("in_Projection", glm::ortho(0.0f, 1800.0f, 0.0f, 1000.0f, 0.0f, 1.0f));
	shader->setUniform("in_Model", model);
	shader->setUniform("in_Texture", texture);

	shader->draw(mesh);
}