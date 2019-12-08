#include "ColorFactory.h"

glm::vec3 ColorFactory::getProduct(COLOR type)
{
	switch (type) {
	case COLOR::RED: return glm::vec3(1, 0, 0);
	case COLOR::GREEN: return glm::vec3(0, 1, 0);
	case COLOR::BLUE: return glm::vec3(0, 0, 1);
	case COLOR::WHITE: return glm::vec3(1, 1, 1);
	case COLOR::BLACK: return glm::vec3(0, 0, 0);
	case COLOR::YELLOW: return glm::vec3(1, 1, 0);
	case COLOR::PURPLE: return glm::vec3(0.5, 0, 0.5);
	case COLOR::PINK: return glm::vec3(1, 0.75, 0.8);
	case COLOR::RANDOM: return glm::vec3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
	default: this->getProduct(COLOR::WHITE);
	}
}
