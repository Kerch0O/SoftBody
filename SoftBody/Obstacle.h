#pragma once
#include "functions.h"

class Obstacle {
public:
	sf::RectangleShape self;
	std::vector<sf::Vector2f> ps;
	float rot;

	Obstacle();
	Obstacle(sf::Vector2f pos, sf::Vector2f size, float r);

	void draw(sf::RenderWindow& window);
};
