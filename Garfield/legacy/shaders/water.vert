uniform mat4 in_Projection;
uniform mat4 in_View;
uniform mat4 in_Model;
uniform float in_Time;

attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Normal;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;



float3 GerstnerWave(vec4 wave, vec3 p, inout float3 tangent, inout float3 binormal) 
{
	float speed = 0.05;
	float steepness = wave.z;
	float wavelength = wave.w;
	float k = 2 * 3.1415926535 / wavelength;
	float c = sqrt(9.8 / k);
	float2 d = normalize(wave.xy);
	float f = k *(dot(d,p.xy) -  c * in_Time * speed);
	float a = -steepness / k;
	// y is z
	
	tangent += float3(-d.x * d.x * (steepness * sin(f)), -d.x * d.y * (steepness * sin(f)), d.x * (steepness * cos(f)));

	binormal += float3(-d.x * d.y * (steepness * sin(f)),-d.y * d.y * (steepness * sin(f)),d.y * (steepness * cos(f)));


	return float3(d.x * (a * cos(f)),d.y * (a * cos(f)),a * sin(f));


}




void main()
{
	// wave A (dirx,diry,steepness,wavelength);
	vec4 waveA = vec4(1.0,1.0,0.25,0.05);
	vec4 waveB = vec4(0.0,0.6,0.25,0.025);
	vec4 waveC = vec4(1.0,1.3,0.25,0.01);
	vec4 waveD = vec4(0.6,0.0,0.25,0.01);

	float3 gridPoint = in_Position;
	float3 tangent = float3(1, 0, 0);
	float3 binormal = float3(0, 0, 1);
	float3 p = gridPoint;
	p += GerstnerWave(waveA, gridPoint, tangent, binormal);
	p += GerstnerWave(waveB, gridPoint, tangent, binormal);
	p += GerstnerWave(waveC, gridPoint, tangent, binormal);
	float3 normal = normalize(cross(binormal, tangent));






	gl_Position = in_Projection * in_View * in_Model * vec4(p, 1.0);
	ex_TexCoord = in_TexCoord;
	
	

	//float3 tangent = normalize(float3(1 - steepness * sin(f) , steepness * cos (f) , 0));

	//float3 normal = float3 (normalize(cross(binormal,tangent)));

	
	//ex_Normal = mat3(in_Model) * in_Normal;
	ex_Normal = mat3(in_Model) * normal;
	ex_FragPos = vec3(in_Model * vec4(in_Position,1.0));
  
}