#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

class VertexArray;
class Texture;
class RenderTexture;

struct Sampler
{
  GLint id;
  Texture *texture;
};

class ShaderProgram
{
  GLuint id;
  std::vector<Sampler> samplers;
  glm::vec4 viewport;
  VertexArray *simpleShape;

public:
  ShaderProgram(std::string vert, std::string frag);
  void draw();
  void draw(RenderTexture *renderTexture);
  void draw(VertexArray *vertexArray);
  void draw(std::shared_ptr<RenderTexture> renderTexture);
  void draw(RenderTexture *renderTexture, VertexArray *vertexArray);
  void draw(std::shared_ptr<RenderTexture>renderTexture, VertexArray *vertexArray);
  void setUniform(std::string uniform, glm::vec3 value);
  void setUniform(std::string uniform, glm::vec4 value);
  void setUniform(std::string uniform, float value);
  void setUniform(std::string uniform, glm::mat4 value);
  void setUniform(std::string uniform, Texture *texture);
  void setUniform(std::string uniform, std::shared_ptr<Texture> texture);

  GLuint getId();
  void setViewport(glm::vec4 viewPort);
  void printShaderInfoLog(GLuint obj);
  void printProgramInfoLog(GLuint obj);

};
