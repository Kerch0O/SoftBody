#pragma once
#include "functions.h"

class spring;

class massPoint {
public:
	float m, g, r;
	sf::Vector2f velocity;

	sf::CircleShape self;
	

	massPoint();

	massPoint(float mass, float gravity, float radius, sf::Vector2f pos);
	void selfColPush(std::vector<std::vector<massPoint>>& m, sf::Vector2i curr, std::vector<std::tuple<massPoint*, sf::Vector2f, sf::Vector2f>> &reflections);
};