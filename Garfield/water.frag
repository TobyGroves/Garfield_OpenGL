uniform sampler2D in_Texture;
uniform sampler2D in_Flow;
uniform mat4 in_Model;
uniform vec3 in_Emissive;
uniform vec3 in_Ambient;
uniform vec3 in_LightPos;
uniform vec3 in_LightColor;
uniform float in_shine;
uniform mat4 in_View;
uniform float in_Time;



varying vec2 ex_TexCoord;
varying vec3 ex_Normal;
varying vec3 ex_FragPos;

vec3 FlowUVW (vec2 uv, vec2 flowVector, vec2 jump,float flowOffset,float tiling, float time, bool flowB);

vec3 specu(vec3 norm,vec3 lightDir);

float frac(float v);

void main()
{
  
  float speed = 0.025;
  float flowStrength = 0.1;
  float flowOffset =0.0;
  float tiling = 1.0;

  vec4 color = vec4(0.0,0.357,0.28,1.0);

  //texture
  //vec4 tex = texture2D(in_Texture, ex_TexCoord);
  
  vec2 flowVector = texture2D(in_Flow, ex_TexCoord).rg;
  flowVector *= flowStrength;
  float noise = texture2D(in_Flow, ex_TexCoord).a;
  float time = in_Time * speed + noise;

  // between - 0.25 and 0.25
  vec2 jump = float2(0.25, 0.25);

  vec3 uvwA = FlowUVW(ex_TexCoord, flowVector * 2 - 1,jump,flowOffset,tiling, time , false);
  vec3 uvwB = FlowUVW(ex_TexCoord, flowVector * 2 - 1,jump,flowOffset,tiling, time , true);

  vec4 texA = texture2D(in_Texture, uvwA.xy) * uvwA.z;
  vec4 texB = texture2D(in_Texture, uvwB.xy) * uvwB.z;


  //emmisive and ambient
  //vec3 lighting = in_Emissive + in_Ambient ;
  
  //texture
  //vec4 tex = texture2D(in_Texture, FlowUVW(ex_TexCoord,flowVector * 2 - 1,in_Time * 0.5));
  //vec4 tex = texture2D(in_Texture, uvw.xy) * uvw.z;

  vec4 tex = (texA + texB) * color;
  //vec4 tex =vec4(flowVector, 0,1);


  vec3 norm = normalize(ex_Normal);
  
  //lighting 
  //diffuse
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);
  float diff = max(dot(norm, lightDir),0.0);
  
  //specular
  vec3 specular = specu(norm,lightDir);
  
  //adding spec and diff
  vec3 lighting = diff + specular + in_Ambient;
  
  //drawing to fragment
  gl_FragColor = tex * vec4(lighting,1);
  
  
  gl_FragColor = tex * vec4(lighting,1);
}

vec3 specu(vec3 norm,vec3 lightDir)
{
  vec4 viewPos = inverse(in_View) * vec4(0,0,0,1);
  vec3 viewDir = normalize(vec3(viewPos) - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir,norm);
  float specu = pow(max(dot(viewDir,reflectDir),0.0),in_shine);

  return (in_LightColor * specu) * vec3 (1,1,1);
}

vec3 FlowUVW (vec2 uv, vec2 flowVector, vec2 jump,float flowOffset,float tiling, float time, bool flowB) {
	float phaseOffset = flowB ? 0.5 : 0;
	float progress = frac(time + phaseOffset);
	vec3 uvw;
	uvw.xy = uv - flowVector * (progress + flowOffset);
	uvw.xy *= tiling;
	uvw.xy += phaseOffset;
	//uvw.xy += (time - progress) * jump;
	uvw.z = 1 - abs(1 - 2 * progress);
	return uvw;
}

float frac(float v)
{
  return v - floor(v);
}