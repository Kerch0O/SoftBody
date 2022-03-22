#pragma once
#include "functions.h"

class spring;

class massPoint {
public:
	float m;
	float g;

	sf::CircleShape self;

	std::vector<spring> springs;

	massPoint();

	massPoint(float mass, float gravity, sf::Vector2f pos);

};