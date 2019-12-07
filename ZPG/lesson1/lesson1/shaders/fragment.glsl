#version 330

#define MAX_LIGHTS 10;


struct Light {
	vec4 position;

	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
};










in vec4 _lightPosition; //pozice svetla
in vec3 ex_worldNormal;	//normala pro fragment
in vec4 ex_worldPosition;	//pozice
in vec2 _uv;	//uv souradnice pro sparvne texturovani




uniform vec4 lightColor; //barva svetla
uniform vec4 objectColor; //barva objektu



uniform vec4 viewPos; //camera


uniform Light lights[10];
uniform int lightsCount;

uniform bool hasObjectTexture;
uniform sampler2D textureUnitId;

out vec4 frag_colour;


vec4 calcAmbient(vec4 objectColor);
vec4 calcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main () {
	vec3 lightVector = vec3(_lightPosition - ex_worldPosition);
	float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)),0.0);

	vec4 diffuse = dot_product * objectColor;
	vec4 ambient = calcAmbient(objectColor);

	vec3 viewDir = vec3(viewPos - ex_worldPosition);
	vec3 reflectDir = reflect(normalize(-lightVector), normalize(ex_worldNormal));

	float spec = pow(max(dot(normalize(viewDir), reflectDir), 0.0), 32);
	vec4 specular = spec * lightColor;

	//frag_colour = (ambient + diffuse + specular);
	frag_colour = (ambient + diffuse + specular);
	if(hasObjectTexture) {
		frag_colour *= texture(textureUnitId, _uv);
	}
};



vec4 calcAmbient(vec4 objectColor) {
	return vec4(0.05, 0.05, 0.05, 1) * objectColor;
}


vec4 calcLight(Light light, vec3 normal, vec4 fragPos, vec4 viewPos, vec4 objectColor) {
	//Vectores which i need!
	vec3 lightDirection = vec3(light.position - fragPos);
	vec3 cameraDirection = vec3(viewPos - fragPos);
	vec3 reflectionDirection =  reflect(normalize(-lightDirection), normalize(normal));


	//Angles i need!
	float diffuseProduct =	max(dot(normalize(lightDirection), normalize(normal)), 0.0);
	float reflectionProduct = max(dot(normalize(cameraDirection), reflectionDirection), 0.0);


	//Calculation of light!
	vec4 diffusePart = diffuseProduct * objectColor * light.diffuse;
	vec4 specularPart = pow(reflectionProduct, 32) * light.specular; 

	return diffusePart + specularPart;
};

