#include "functions.h"


massPoint::massPoint(float mass, float gravity, sf::Vector2f pos)
	: m(mass), g(gravity), velocity(sf::Vector2f(0.0f, 0.0f))
{
	self.setRadius(5.0f);
	self.setOrigin(5.0f, 5.0f);
	self.setPosition(pos);
	self.setFillColor(sf::Color(255, 0, 0, 255));
}