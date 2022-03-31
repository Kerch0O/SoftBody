#include "functions.h"


massPoint::massPoint(float mass, float gravity, float radius, sf::Vector2f pos)
	: m(mass), g(gravity), r(radius), velocity(sf::Vector2f(0.0f, 0.0f))
{
	self.setRadius(radius);
	self.setOrigin(radius, radius);
	self.setPosition(pos);
	self.setFillColor(sf::Color(255, 0, 0, 255));
}

void massPoint::selfColPush(std::vector<std::vector<massPoint>>& m, sf::Vector2i curr) {
	//This stops the structure from collapsing in on itself
	//It collapses when the force of a string pulls a massPoint through another massPoint, making them sit inside of eachover
	//This removes the error py pushing out any colliding points
	//It will then push it out using a normalised push vector and reflect it using 
	//r = v - 2n(v.n / mag(n))
	//v.n is the dot product, and is calculated by v.x * n.x + v.y * n.y
	//n(v.n / mag(n)) is the formula for calculating the projected length of v onto n, projnv
	//simple geometry allows us to reconfigure the reflection vector and add it to the original vector so that it reaches the normal

	//curr is the index position of this massPoint
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			if (sf::Vector2i(i, j) != curr) {
				pushNormalR(m[curr.x][curr.y], m[i][j]);
			}
		}
	}
}