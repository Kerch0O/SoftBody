#pragma once
#include "functions.h"

class massPoint;

class spring {
public:
	float damping, k, aL;

	massPoint& p1;
	massPoint& p2;

	sf::RectangleShape self;

	spring();
	spring(massPoint &p11, massPoint &p21, sf::Vector2f pos, float d, float sc, float anchor);

	void rectRefresh(std::vector<std::vector<massPoint>> m);
	void physics(std::vector<std::vector<massPoint>>& m);

};