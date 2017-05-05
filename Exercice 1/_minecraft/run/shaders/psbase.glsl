varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;

uniform float ambientLevel;
uniform mat4 view;
uniform vec3 camPos;
uniform vec3 lightPos;

in vec4 world_pos;
in vec3 world_normal;

void main()
{
	// Scaling The Input Vector To Length 1
	vec3 normalized_normal = normalize(normal);
	vec3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);

	// Calculating The Diffuse Term And Clamping It To [0;1]
	float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);

	//CONTOURING
	/*vec3 world_pos_vec = vec3(world_pos);

	vec3 L = normalize(vertex_to_light_vector - world_pos_vec);
	vec3 V = normalize(camPos - world_pos_vec);
	vec3 H = normalize(L+V);

	float edgeDetection = (dot(V, world_normal) > 0.3) ? 1 : 0;
	float light = edgeDetection * (DiffuseTerm*(1-ambientLevel) + ambientLevel);

	vec4 colorT = vec4(light, light, light, 1);*/
	
	float intensity;

	vec4 colorT;

	intensity = dot(normalized_vertex_to_light_vector, normalized_normal);

	if (intensity > 0.95)
	{
		colorT = vec4(1.0, 0.5, 0.5, 1.0);
	}
	else if (intensity > 0.5)
	{
		colorT = vec4(0.6, 0.3, 0.3, 1.0);
	}
	else if (intensity > 0.25)
	{
		colorT = vec4(0.4, 0.2, 0.2, 1.0);
	}
	else
	{
		colorT = vec4(0.2,0.1,0.1,1.0);
	}

	gl_FragColor = colorT * color;
}