#include "functions.h"


spring::spring(int m1, int m2, sf::Vector2f pos, float d, float sc, float anchor)
	: iM1(m1), iM2(m2), damping(d), k(sc), aL(anchor)
{
	self.setPosition(pos);
	self.setFillColor(sf::Color::Black);
}