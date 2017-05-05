varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;

uniform float elapsed;
uniform mat4 invertView;
uniform mat4 view;
uniform vec3 camPos;
uniform vec3 lightPos;

out vec4 world_pos;
out vec3 world_normal;

float rand(vec2 co){
		return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	mat4 modelMatrix = invertView * gl_ModelViewMatrix;

	world_pos =  modelMatrix * gl_Vertex;
	world_normal = normalize(mat3(modelMatrix) * normal);

 	if(gl_Color.b > 0.5)
 	{
 		world_pos.z += sin((rand(vec2(world_pos.x,world_pos.y))/10.0+world_pos.x+elapsed)*2)*3;
 	}

	world_pos.z -=length(camPos-vec3(world_pos))-5;

 	gl_Position = gl_ProjectionMatrix * view * world_pos;

 	// Transforming The Normal To ModelView-Space
	normal = gl_NormalMatrix * gl_Normal; 

	//Direction lumiere
	vertex_to_light_vector = vec3(gl_LightSource[0].position);

	//Couleur
	color = gl_Color;
}