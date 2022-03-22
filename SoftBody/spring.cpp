#include "functions.h"


spring::spring(int im1, int jm1, int im2, int jm2, sf::Vector2f pos, float d, float sc, float anchor)
	: iM1(im1), jM1(im2), iM2(im2), jM2(jm2), damping(d), k(sc), aL(anchor)
{
	self.setPosition(pos);
	self.setFillColor(sf::Color::Black);
}