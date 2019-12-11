#version 330

#define MAX_LIGHTS 10


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
in vec4 fragPosLightSpace;



//uniform vec4 lightColor; //barva svetla
uniform vec4 objectColor; //barva objektu



uniform vec4 viewPos; //camera

uniform Light flashlight; //FlashLight
uniform Light lights[MAX_LIGHTS];

uniform int lightsCount;

//LIGHTS
uniform PointLight pointLights[MAX_LIGHTS];
uniform int pointLightsCount;


uniform SpotLight spotLights[MAX_LIGHTS];
uniform int spotLightsCount;

uniform DirectionLight directionLight;


uniform bool hasObjectTexture;
uniform sampler2D textureUnitId;
uniform sampler2D shadowMap;

out vec4 frag_colour;


vec4 calcAmbient(vec4 objectColor);
vec4 calcLight(Light light, vec3 normal, vec4 fragPos, vec4 viewPos, vec4 objectColor);
vec4 calcFlashLight();
float calcAttenuation(Light light);
vec4 calcAmbientForLight(Light light);
vec4 calcSpotLight(Light light);


vec4 calcDirectionLight(DirectionLight light, vec3 viewDirection, vec4 objColor);
vec4 calcSpotLight(SpotLight light, vec3 viewDirection, vec4 objColor);
vec4 calcPointLight(PointLight light, vec3 viewDirection, vec4 objColor);

vec4 sumSpotLight(vec3 viewDirection, vec4 objColor);
vec4 sumPointLight(vec3 viewDirection, vec4 objColor);
vec4 sumFlashLight(vec3 viewDirection, vec4 objColor);
float calcShadow(float dotLightNormal);


void main () {

	vec4 objTexture = texture(textureUnitId, _uv);
	vec4 objColor = objectColor;

	if(hasObjectTexture) {
		objColor *= objTexture;
	}

	//vec4 finalLight = calcAmbient(objectColor);
	vec4 totalLight;
//	for(int i = 0; i < lightsCount; i++) {
//		totalLight += calcLight(lights[i], ex_worldNormal, ex_worldPosition, viewPos, objectColor);
//		totalLight += calcAmbientForLight(lights[i]);
//	}
	//totalLight += calcFlashLight();

	vec3 viewDirection = vec3(normalize(viewPos - ex_worldPosition));
	totalLight += sumPointLight(viewDirection, objColor);
	//sumPointLight(viewDirection, objColor);
	totalLight += sumSpotLight(viewDirection, objColor);
	//sumSpotLight(viewDirection, objColor);
	totalLight += sumFlashLight(viewDirection, objColor);
	totalLight += calcDirectionLight(directionLight, viewDirection, objColor);


	frag_colour = objColor * totalLight;
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



vec4 calcDirectionLight(DirectionLight light, vec3 viewDirection, vec4 objColor) {


	vec3 reflectionDirection = reflect(normalize(-light.direction), normalize(ex_worldNormal));
	float dotLightNormal = dot(normalize(vec3(light.direction)), normalize(ex_worldNormal));
	float diff = max(dot(normalize(ex_worldNormal), normalize(-light.direction)), 0.0);
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);
	vec4 ambientPart = light.ambient;;
	vec4 diffusePart = light.diffuse * diff;
	vec4 specularPart = light.specular * spec;

	//float shadow = calcShadow(dotLightNormal);
	float shadow = 1;
	vec4 finalLighting = (shadow * (diffusePart + specularPart) + ambientPart) * objColor;


	return finalLighting;
};

vec4 calcSpotLight(SpotLight light, vec3 viewDirection, vec4 objColor) {
	vec3 lightDirection = vec3(light.position - ex_worldPosition);

	float diff = max(dot(normalize(ex_worldNormal), normalize(lightDirection)), 0.0);

	vec3 reflectionDirection = reflect(normalize(-lightDirection), normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);

	float dist = length(light.position - ex_worldPosition);
	float attenuation =  1.0 / (light.constant + light.lienar * dist + light.quadratic * (dist * dist));

	float theta = dot(normalize(lightDirection), normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec4 ambientPart = light.ambient * objColor;
	vec4 diffusePart = light.diffuse * diff * objColor;
	vec4 specularPart = light.specular * spec * objColor;

	ambientPart *= attenuation * intensity;
	diffusePart *= attenuation * intensity;
	specularPart *= attenuation * intensity;
	return (ambientPart + diffusePart + specularPart);
};


vec4 calcPointLight(PointLight light, vec3 viewDirection, vec4 objColor) {
	vec3 lightDirection = vec3(light.position - ex_worldPosition);
	float diff = max(dot(normalize(ex_worldNormal), normalize(lightDirection)), 0.0);

	vec3 reflectionDirection = reflect(normalize(-lightDirection), normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);

	float dist = length(light.position - ex_worldPosition);
	float attenuation =  1.0 / (light.constant + light.lienar * dist + light.quadratic * (dist * dist));
 
	vec4 ambientPart = light.ambient * objColor;
	vec4 diffusePart = light.diffuse * diff * objColor;
	vec4 specularPart = light.specular * spec * objColor;


	ambientPart *= attenuation;
	diffusePart *= attenuation;
	specularPart *= attenuation;
	return (ambientPart + diffusePart + specularPart);
};

vec4 sumSpotLight(vec3 viewDirection, vec4 objColor) {
	vec4 totalSpotLight;
	for(int i = 0; i < spotLightsCount; i++) {
		totalSpotLight += calcSpotLight(spotLights[i], viewDirection, objColor);
	}
	return totalSpotLight;
}

vec4 sumPointLight(vec3 viewDirection, vec4 objColor) {
	vec4 totalPointLight;
	for(int i = 0; i < pointLightsCount; i++) {
		totalPointLight += calcPointLight(pointLights[i], viewDirection, objColor);
	}
	return totalPointLight;
};

vec4 sumFlashLight(vec3 viewDirection, vec4 objColor) {
		vec3 lightDirection = vec3(flashlight.position - ex_worldPosition);

	float diff = max(dot(normalize(ex_worldNormal), normalize(lightDirection)), 0.0);

	vec3 reflectionDirection = reflect(normalize(-lightDirection), normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32);

	float dist = length(flashlight.position - ex_worldPosition);
	float attenuation =  1.0 / (flashlight.constant + flashlight.linear * dist + flashlight.quadratic * (dist * dist));

	float theta = dot(normalize(lightDirection), normalize(-flashlight.direction));
	float epsilon = flashlight.cutOff - flashlight.outerCutOff;
	float intensity = clamp((theta - flashlight.outerCutOff) / epsilon, 0.0, 1.0);

	vec4 ambientPart = flashlight.ambient * objColor;
	vec4 diffusePart = flashlight.diffuse * diff * objColor;
	vec4 specularPart = flashlight.specular * spec * objColor;

	ambientPart *= attenuation * intensity;
	diffusePart *= attenuation * intensity;
	specularPart *= attenuation * intensity;
	return (ambientPart + diffusePart + specularPart);
}


float calcShadow(float dotLightNormal) {
	vec3 pos = fragPosLightSpace.xyz * 0.5 + 0.5;
	if(pos.z > 1.0) {
		pos.z = 1.0;
	}
	float depth = texture(shadowMap, pos.xy).r;
	float bias = max(0.05 * (1.0 - dotLightNormal), 0.005);
	return (depth + bias) < pos.z ? 0.0 : 1.0;
	//float depth = 0;
	//return depth < pos.z ? 0.0 : 1.0;
};
