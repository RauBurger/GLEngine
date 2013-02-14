#version 150 //;
#define MAX_LIGHTS 17 //;
uniform int numLights;
uniform vec3 light1;
uniform vec3 light2;
uniform mat3 vNormMat;
uniform mat4 mvpMat;
uniform mat4 mvMat;
uniform mat4 mMat;

//attribute vec3 vVert;
//attribute vec3 vNorm;
in vec3 vVert;
in vec3 vNorm;

smooth out vec3 lp;
smooth out vec3 lightVec[MAX_LIGHTS];
smooth out vec3 normal;
smooth out vec4 color;
smooth out vec3 fPos;
//out vec4 position;

//varying vec3 lp;
//varying vec3 lightVec[MAX_LIGHTS];
//varying vec3 normal;
//varying vec4 color;
//varying vec3 fPos;

void main()
{
	
	lp = light1;
    // Get surface normal in eye coordinates;
    normal = vNormMat * vNorm;
	//normal = vNorm;
    // Get vertex position in eye coordinates;
    //vec3 vPosition4 = vNormMat * vVert;
	vec4 vPosition4 = mMat * vec4(vVert, 1.0f);
	//vec4 vPosition4 = vec4(vVert, 1.0);
	//vec4 vPosition4 = mvMat * vec4(vVert, 1.0f);
	//fPos = vPosition4;
	fPos = vPosition4.xyz / vPosition4.w;
	
    // Get vector to light source;
    //lightVec[0] = normalize(light1 - vPosition3);
	lightVec[0] = light1 - fPos;
	
    // Don't forget to transform the geometry!;
    gl_Position = mvpMat * vec4(vVert, 1.0);
	//position = mvpMat * vec4(vVert, 1.0);
	
	color = vec4(1.0, 1.0, 1.0, 1.0);

}