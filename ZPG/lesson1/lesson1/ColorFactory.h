#pragma once
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
enum class COLOR {
	RED,
	GREEN,
	BLUE,
	WHITE,
	BLACK,
	YELLOW,
	PURPLE,
	PINK,
	RANDOM
};

class ColorFactory
{
public:
	glm::vec3 getProduct(COLOR type);
private:
};

