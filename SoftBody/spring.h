#pragma once
#include "functions.h"

class massPoint;

class spring {
public:
	float damping;
	float k;
	float aL;

	int iM1; //Index positions of connected mass points
	int iM2;

	sf::RectangleShape self;

	spring();
	spring(int m1, int m2, sf::Vector2f pos, float d, float sc, float anchor);

};