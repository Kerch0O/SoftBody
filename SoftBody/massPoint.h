#pragma once
#include "functions.h"

class spring;

class massPoint {
public:
	float m, g;
	sf::Vector2f velocity;

	sf::CircleShape self;


	massPoint();

	massPoint(float mass, float gravity, sf::Vector2f pos);

};