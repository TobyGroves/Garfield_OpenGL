uniform sampler2D in_Texture;
uniform mat4 in_Model;
uniform vec3 in_Emissive;
uniform vec3 in_Ambient;

varying vec2 ex_TexCoord;
void main()
{
  //texture
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  
  //emmisive and ambient
  vec3 lighting = in_Emissive + in_Ambient ;
  
  
  
  gl_FragColor = tex * vec4(lighting,1);
}
