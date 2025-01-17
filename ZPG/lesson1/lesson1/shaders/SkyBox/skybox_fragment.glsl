#version 330
in vec3 TexCoords;

uniform samplerCube textureUnitId;

uniform vec4 objectColor; //barva objektu
uniform bool hasObjectTexture;

out vec4 frag_colour;

void main () {
	frag_colour = objectColor;
	frag_colour = texture(textureUnitId, TexCoords);
};
