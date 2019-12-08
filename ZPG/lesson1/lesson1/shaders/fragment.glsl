#version 330

#define MAX_LIGHTS 10;


struct Light {
	vec4 position;

	vec3 direction; //FlashLight
	float cutOff;	//FlashLight

	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
};










//in vec4 _lightPosition; //pozice svetla
in vec3 ex_worldNormal;	//normala pro fragment
in vec4 ex_worldPosition;	//pozice
in vec2 _uv;	//uv souradnice pro sparvne texturovani




//uniform vec4 lightColor; //barva svetla
uniform vec4 objectColor; //barva objektu



uniform vec4 viewPos; //camera

uniform Light flashlight; //FlashLight
uniform Light lights[10];

uniform int lightsCount;

uniform bool hasObjectTexture;
uniform sampler2D textureUnitId;

out vec4 frag_colour;


vec4 calcAmbient(vec4 objectColor);
vec4 calcLight(Light light, vec3 normal, vec4 fragPos, vec4 viewPos, vec4 objectColor);
vec4 calcFlashLight();


void main () {

	vec4 objTexture = texture(textureUnitId, _uv);
	vec4 objColor = objectColor;

	if(hasObjectTexture) {
		objColor *= objTexture;
	}

	vec4 finalLight = calcAmbient(objectColor);
	for(int i = 0; i < lightsCount; i++) {
		finalLight += calcLight(lights[i], ex_worldNormal, ex_worldPosition, viewPos, objectColor);
	}
	finalLight += calcFlashLight();


	frag_colour = objColor * finalLight;
};



vec4 calcAmbient(vec4 objectColor) {
	return vec4(0.0, 0.0, 0.0, 1) * objectColor;
}


vec4 calcLight(Light light, vec3 normal, vec4 fragPos, vec4 viewPos, vec4 objectColor) {
	//Vectores which i need!
	vec3 lightDirection = vec3(light.position - fragPos);
	vec3 cameraDirection = vec3(viewPos - fragPos);
	vec3 reflectionDirection =  reflect(normalize(-lightDirection), normalize(normal));


	//Angles i need!
	float diffuseProduct =	max(dot(normalize(lightDirection), normalize(normal)), 0.0);
	float reflectionProduct = max(dot(normalize(cameraDirection), reflectionDirection), 0.0);


	//Wtf is this
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (1 + 0.09 * distance + 0.032 * (distance * distance));

	//Calculation of light!
	vec4 diffusePart = diffuseProduct * objectColor * light.diffuse;
	vec4 specularPart = pow(reflectionProduct, 32) * light.specular; 

	return (diffusePart * attenuation) + (specularPart* attenuation);
};

vec4 calcFlashLight() {
	vec3 lightDirection = vec3(flashlight.position - ex_worldPosition);
	float theta = dot(lightDirection, normalize(-flashlight.direction));

	if(theta > flashlight.cutOff) {
		return calcLight(flashlight, ex_worldNormal, ex_worldPosition, viewPos, objectColor) + flashlight.ambient;
	}
	else {
		return flashlight.ambient;
	}
};
