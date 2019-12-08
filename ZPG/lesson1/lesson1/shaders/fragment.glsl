#version 330

#define MAX_LIGHTS 10;


struct DirectionLight {
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


struct PointLight {
	vec4 position;

	float constant;
	float lienar;
	float quadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct SpotLight {
	vec4 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float lienar;
	float quadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};







struct Light {
	vec4 position;

	vec3 direction; //FlashLight
	float cutOff;	//FlashLight
	float outerCutOff;

	vec4 diffuse;
	vec4 specular;
	vec4 ambient;

	float constant;
	float linear;
	float quadratic;
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
float calcAttenuation(Light light);
vec4 calcAmbientForLight(Light light);
vec4 calcSpotLight(Light light);


vec4 calcDirectionLight(DirectionLight light, vec3 viewDirection, vec4 objectColor);
vec4 calcSpotLight(SpotLight light, vec3 viewDirection, vec4 objectColor);
vec4 calcPointLight(PointLight light, vec3 viewDirection, vec4 objectColor);

vec4 sumSpotLight(vec3 viewDirection, vec4 objectColor);
vec4 sumPointLight(vec3 viewDirection, vec4 objectColor);


void main () {

	vec4 objTexture = texture(textureUnitId, _uv);
	vec4 objColor = objectColor;

	if(hasObjectTexture) {
		objColor *= objTexture;
	}

	//vec4 finalLight = calcAmbient(objectColor);
	vec4 finalLight;
	for(int i = 0; i < lightsCount; i++) {
		finalLight += calcLight(lights[i], ex_worldNormal, ex_worldPosition, viewPos, objectColor);
		finalLight += calcAmbientForLight(lights[i]);
	}
	finalLight += calcFlashLight();

	frag_colour = objColor * finalLight;
};



vec4 calcAmbient(vec4 objectColor) {
	return vec4(0.0, 0.0, 0.0, 1) * objectColor;
};

vec4 calcAmbientForLight(Light light) {
	return light.ambient * calcAttenuation(light);
};


float calcAttenuation(Light light) {
	float distance = length(light.position - ex_worldPosition);
	return 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
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
	//float distance = length(light.position - fragPos);
	//float attenuation = 1.0 / (1 + 0.09 * distance + 0.032 * (distance * distance));
	
	//Calculation of light!
	vec4 diffusePart = diffuseProduct * objectColor * light.diffuse * calcAttenuation(light);
	vec4 specularPart = pow(reflectionProduct, 32) * light.specular * calcAttenuation(light); 

	return (diffusePart) + (specularPart);
};


vec4 calcSpotLight(Light light) {
	vec3 lightDirection = vec3(flashlight.position - ex_worldPosition);
	float theta = dot(lightDirection, normalize(-flashlight.direction));

	if(theta > flashlight.cutOff) {
		float epsilon = (flashlight.cutOff - flashlight.outerCutOff);
		float intensity = clamp((theta / flashlight.outerCutOff) / epsilon, 0.0, 1.0);
		vec4 diffuse_spectacular = calcLight(flashlight, ex_worldNormal, ex_worldPosition, viewPos, objectColor);
		return diffuse_spectacular * intensity + calcAmbientForLight(flashlight);
	}
	else {
		return flashlight.ambient;
	}
}

vec4 calcFlashLight() {
	return calcSpotLight(flashlight);
};



vec4 calcDirectionLight(DirectionLight light, vec3 viewDirection, vec4 objectColor) {
	vec3 reflectionDirection = reflect(normalize(-light.direction), normalize(ex_worldNormal));
	float diff = max(dot(ex_worldNormal, normalize(-light.direction)), 0.0);
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 1);
	vec4 ambientPart = light.ambient * objectColor;
	vec4 diffusePart = light.diffuse * diff * objectColor;
	vec4 specularPart = light.specular * spec * objectColor;
	return ambientPart + diffusePart + specularPart;
};
vec4 calcSpotLight(SpotLight light, vec3 viewDirection, vec4 objectColor) {
	vec3 lightDirection = vec3(light.position - ex_worldPosition);

	float diff = max(dot(normalize(ex_worldNormal), normalize(lightDirection)), 0.0);

	vec3 reflectionDirection = reflect(normalize(-lightDirection), normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 1);

	float dist = length(light.position - ex_worldPosition);
	float attenuation =  1.0 / (light.constant + light.lienar * dist + light.quadratic * (dist * dist));

	float theta = dot(normalize(lightDirection), normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec4 ambientPart = light.ambient * objectColor;
	vec4 diffusePart = light.diffuse * diff * objectColor;
	vec4 specularPart = light.specular * spec * objectColor;

	ambientPart *= attenuation * intensity;
	diffusePart *= attenuation * intensity;
	specularPart *= attenuation * intensity;
	return (ambientPart + diffusePart + specularPart);
};


vec4 calcPointLight(PointLight light, vec3 viewDirection, vec4 objectColor) {
	vec3 lightDirection = vec3(light.position - ex_worldPosition);
	float diff = max(dot(normalize(ex_worldNormal), normalize(lightDirection)), 0.0);

	vec3 reflectionDirection = reflect(normalize(-lightDirection), normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 1);

	float dist = length(light.position - ex_worldPosition);
	float attenuation =  1.0 / (light.constant + light.lienar * dist + light.quadratic * (dist * dist));
 
	vec4 ambientPart = light.ambient * objectColor;
	vec4 diffusePart = light.diffuse * diff * objectColor;
	vec4 specularPart = light.specular * spec * objectColor;


	ambientPart *= attenuation;
	diffusePart *= attenuation;
	specularPart *= attenuation;
	return (ambientPart + diffusePart + specularPart);
};

vec4 sumSpotLight(vec3 viewDirection, vec4 objectColor);
vec4 sumPointLight(vec3 viewDirection, vec4 objectColor);
