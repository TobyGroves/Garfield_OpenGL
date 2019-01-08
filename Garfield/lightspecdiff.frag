uniform sampler2D in_Texture;

//uniform sampler2D in_NormalMap;

uniform vec3 in_LightPos;
uniform mat4 in_Model;
uniform vec3 in_LightColor;
uniform float in_shine;
uniform mat4 in_View;
uniform vec3 in_Ambient;

varying vec2 ex_TexCoord;
varying vec3 ex_Normal;
varying vec3 ex_FragPos;

void main()
{
  //texture
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  
  //vec3 norm = texture2D(in_NormalMap, ex_TexCoord);
  //norm = normalize(normal * 2.0 - 1.0);
  vec3 norm = normalize(ex_Normal);
  
  //lighting 
  //diffuse
  //vec3 lightDir = normalize(ex_FragPos - (inverse(in_View) * vec4(in_LightPos,1)));
  //vec3 lightDir = normalize(ex_FragPos - in_LightPos);
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);
  float diff = max(dot(norm, lightDir),0.0);
  
  //specular
  
  vec4 viewPos = inverse(in_View) * vec4(0,0,0,1);
  vec3 viewDir = normalize(vec3(viewPos) - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir,norm);
  float specu = pow(max(dot(viewDir,reflectDir),0.0),in_shine);
  vec3 specular = (in_LightColor * specu) * vec3 (1,1,1);
  
  //adding spec and diff
  vec3 lighting = diff + specular + in_Ambient;
  
  //drawing to fragment
  gl_FragColor = tex * vec4(lighting,1);
}