#version 330
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;
uniform mat4 modelMatrix; //poslani matice dovnitr
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrix;
//uniform vec3 lightPosition;

out vec2 _uv;
//out vec4 _lightPosition;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec4 fragPosLightSpace;

void main () {
	gl_Position = (projectionMatrix*viewMatrix*modelMatrix) * vec4(position, 1.0);
	//_lightPosition = vec4(lightPosition, 1.0f);
	mat4 tmp = lightSpaceMatrix;
	vec4 worldPos = modelMatrix * vec4(position, 1.0f);
	vec3 normalPos = transpose(inverse(mat3(modelMatrix))) * normal;

	//new shadowmaping
	fragPosLightSpace = lightSpaceMatrix * vec4(position, 1);
	//
	_uv = uv;
	ex_worldPosition = worldPos;
	ex_worldNormal = normalPos;

	//ex_worldPosition = vec3(worldPos.x, worldPos.y, worldPos.z);
	//ex_worldNormal = vec3(normalPos.x, normalPos.y, normalPos.z);
};