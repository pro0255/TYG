#version 330


//TODO udelat funkce
//ASIMP
//Doresit textury
out vec4 frag_colour;

//in vec3 _lightPosition;
//in vec3 ex_worldNormal;
//in vec3 ex_worldPosition;


in vec4 _lightPosition;
in vec3 ex_worldNormal;
in vec4 ex_worldPosition;
in vec2 _uv;

uniform vec4 lightColor;
uniform vec4 objectColor;
uniform vec4 viewPos;
uniform sampler2D textureUnitId;


void main () {
	vec3 lightVector = vec3(_lightPosition - ex_worldPosition);
	float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)),0.0);

	vec4 diffuse = dot_product * objectColor;
	vec4 ambient = vec4(0.05, 0.05, 0.05, 1) * objectColor;

	vec3 viewDir = vec3(viewPos - ex_worldPosition);
	vec3 reflectDir = reflect(normalize(-lightVector), normalize(ex_worldNormal));

	float spec = pow(max(dot(normalize(viewDir), reflectDir), 0.0), 32);
	vec4 specular = spec * lightColor;
	

    //frag_colour = ambient + diffuse + specular;
	frag_colour = (ambient + diffuse + specular) * texture(textureUnitId, _uv);
};