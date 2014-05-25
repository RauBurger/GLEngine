#define MAX_LIGHTS 17 //;
uniform sampler2D baseTex;
uniform sampler2D heightMap;
uniform vec3 CAMERA_POSITION;
uniform int fpNumLights;
varying vec3 normal;
varying vec3 position;
varying vec3 lightVec[MAX_LIGHTS];
varying vec4 color;

void main()
{
	gl_FragColor = vec4(0);

	for(int i = 0; i < fpNumLights; i++)
	{
		vec3 norm = texture2D(heightMap, gl_TexCoord[0].st).rgb * 2.0 - 1.0;
		vec3 baseColor = texture2D(baseTex, gl_TexCoord[0].st).rgb;


		float diff = max(0.0, dot(normalize(norm), normalize(lightVec[i])));

		gl_FragColor += diff * gl_LightSource[i].diffuse * vec4(baseColor, 1.0) * color;

		gl_FragColor += gl_LightSource[i].ambient;

		vec3 reflection = normalize(reflect(-normalize(lightVec[i]),normalize(norm)));

		float spec = max(0.0, dot(normalize(norm), reflection));
		
		if(diff != 0.0)
		{
			vec3 cameraVector = normalize(CAMERA_POSITION - position);
			vec3 halfVector = normalize(lightVec[i] + cameraVector);
			float nxHalf = max(0.0, dot(norm, halfVector));
			float fSpec = pow(spec, 128.0);
			gl_FragColor.rgb += vec3(fSpec, fSpec, fSpec);
		}
	}
}

