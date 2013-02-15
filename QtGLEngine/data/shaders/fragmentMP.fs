#version 150 //;
#define MAX_LIGHTS 17 //;
uniform int fpNumLights;
uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 camPos;
uniform mat4 WMatrix;
uniform mat3 WorldRot;

smooth in vec3 lp;
smooth in vec3 normal;
smooth in vec3 lightVec[MAX_LIGHTS];
smooth in vec4 color;
smooth in vec3 fPos;
//varying vec3 lp;
//varying vec3 normal;
//varying vec3 lightVec[MAX_LIGHTS];
//varying vec4 color;
//varying vec3 fPos;

//vec4 lit(float NdotL, float NdotH, float m);
out vec4 FragColor;

void main()
{

	
	//vec3 lightVec1 = lightPos1 - fPos;
	vec3 lightVec1 = fPos - lightPos1;
	//lightVec1 = normalize(lightVec1);
	
	// Dot product gives us diffuse intensity;
    //float diff = max(0.0, dot(normalize(normal), normalize(lightVec[0])));
	float diff = max(0.0, dot(normalize(normal), normalize(lightVec1)));
	
    // Multiply intensity by diffuse color, force alpha to 1.0;
    FragColor = diff * color * vec4(0.3, 0.3, 0.3, 1.0);
	
    // Add in ambient light;
    //FragColor += vec4(0.2, 0.2, 0.2, 1.0);
	//gl_FragColor += vec4(0.0, 0.0, 0.0, 1.0);
	//ambientColor;
	
	
    // Specular Light;
    //vec3 vReflection = normalize(reflect(-normalize(lightVec[0]), normalize(normal)));
	vec3 vReflection = normalize(reflect(-normalize(lightVec1), normalize(normal)));
	
    float spec = max(0.0, dot(normalize(normal), vReflection));
	
    if(diff != 0.0)
	{
		float fSpec = pow(spec, 512.0);
        //float fSpec = pow(spec, 128.0);
		//float fSpec = pow(spec, 256.0);
        FragColor.rgb += vec3(fSpec, fSpec, fSpec);
	}
	//FragColor.rgb = normal;
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//FragColor.rgb += normal;
	//gl_FragColor.rgb = lightPos1;
	//gl_FragColor.rgb = fPos;
	//gl_FragColor.rgb = lightVec1;
}