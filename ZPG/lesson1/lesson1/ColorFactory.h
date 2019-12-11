#pragma once
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
enum class COLOR {
	red,
	green,
	blue,
	white,
	black,
	yellow,
	purple,
	pink,
	random
};

static class ColorFactory
{
public:
	static auto getProduct(COLOR type)->glm::vec3;
	static glm::vec3 getProduct(int r, int g, int b);
	static glm::vec3 getProduct();
};

