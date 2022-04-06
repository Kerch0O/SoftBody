#include "functions.h"

Obstacle::Obstacle(sf::Vector2f pos, sf::Vector2f size, float r) 
	: rot(r){
	self.setFillColor(sf::Color(0, 0, 0, 0));
	self.setOutlineColor(sf::Color::Black);
	self.setOrigin(size / 2.0f);
	self.setSize(size);
	self.setPosition(pos);
	self.setRotation(r);
	self.setOutlineThickness(2.0f);

	ps.push_back(calcCorner(size, pos, r, 1));
	ps.push_back(calcCorner(size, pos, r, 2));
	ps.push_back(calcCorner(size, pos, r, 3));
	ps.push_back(calcCorner(size, pos, r, 4));

}

void Obstacle::draw(sf::RenderWindow& window) {
	window.draw(self);
}
