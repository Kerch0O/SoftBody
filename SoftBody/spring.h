#pragma once
#include "functions.h"

class massPoint;

class spring {
public:
	float damping;
	float k;
	float aL;

	int iM1; //Index positions of connected mass points
	int jM1;
	int iM2;
	int jM2;

	sf::RectangleShape self;

	spring();
	spring(int im1, int jm1, int im2, int jm2, sf::Vector2f pos, float d, float sc, float anchor);

};