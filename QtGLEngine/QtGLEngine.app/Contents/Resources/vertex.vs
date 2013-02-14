#define MAX_LIGHTS 17 //;
uniform int numLights;
varying vec3 lightVec[MAX_LIGHTS];
varying vec3 normal;
varying vec3 position;
varying vec4 color;

void main()
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;

	normal = gl_NormalMatrix * gl_Normal;
	vec3 tangent;
	vec3 binormal;

	vec3 c1 = cross(normal, vec3(0.0, 0.0, -1.0));
	vec3 c2 = cross(normal, vec3(0.0, 1.0, 0.0));

	if(length(c1) > length(c2))
	{
		tangent = c1;
	}
	else
	{
		tangent = c2;
	}

	tangent = normalize(tangent);

	binormal = cross(normal, tangent);
	binormal = normalize(binormal);

	mat3 TBNMatrix = mat3(tangent, binormal, normal);

	vec4 pos = gl_ModelViewMatrix * gl_Vertex;
	position = pos.xyz / pos.w;

	for(int i = 0; i < numLights; i++)
	{
		lightVec[i] = normalize((gl_LightSource[i].position).xyz - position);
		lightVec[i] *= TBNMatrix;
	}
	color = gl_Color;
}

