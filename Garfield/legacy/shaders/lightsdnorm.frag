uniform sampler2D in_Texture;

uniform sampler2D in_NormalMap;

uniform vec3 in_LightPos;
//uniform vec3 in_LightPos[];
uniform mat4 in_Model;
uniform vec3 in_LightColor;
//uniform vec3 in_LightColor[];
uniform float in_shine;
uniform mat4 in_View;

uniform vec3 in_Ambient;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

void main()
{
  //texture
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  
  vec3 norm = texture2D(in_NormalMap, ex_TexCoord).rgb;
  norm = normalize(norm);
  //norm = normalize(norm * 2.0 - 1.0);
  // y and z flip
  norm = normalize(ex_Normal * norm);
  

  //lighting 
  //diffuse
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);
  float diff = max(dot(norm, lightDir),0.0);
  
  //specular
  
  vec4 viewPos = inverse(in_View) * vec4(0,0,0,1);
  vec3 viewDir =  normalize(ex_Normal) * normalize(vec3(viewPos) - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir,normalize(ex_Normal));
  float specu = pow(max(dot(viewDir,reflectDir),0.0),in_shine);
  vec3 specular = (in_LightColor * specu) * vec3 (1,1,1);
  
  //adding spec and diff
  //diff = 0.1;

  vec3 lighting = diff + in_Ambient; //+ specular;
  
  //drawing to fragment
  gl_FragColor = tex * vec4(lighting,1);
}