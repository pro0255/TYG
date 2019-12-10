#include "ColorFactory.h"

auto ColorFactory::getProduct(COLOR type) -> glm::vec3
{
	switch (type) {
	case COLOR::red: return glm::vec3(1, 0, 0);
	case COLOR::green: return glm::vec3(0, 1, 0);
	case COLOR::blue: return glm::vec3(0, 0, 1);
	case COLOR::white: return glm::vec3(1, 1, 1);
	case COLOR::black: return glm::vec3(0, 0, 0);
	case COLOR::yellow: return glm::vec3(1, 1, 0);
	case COLOR::purple: return glm::vec3(0.5, 0, 0.5);
	case COLOR::pink: return glm::vec3(1, 0.75, 0.8);
	case COLOR::random: return glm::vec3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	}
	getProduct(COLOR::white);
}
