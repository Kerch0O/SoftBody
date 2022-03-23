#include "functions.h"


spring::spring(int im1, int jm1, int im2, int jm2, sf::Vector2f pos, float d, float sc, float anchor)
	: iM1(im1), jM1(jm1), iM2(im2), jM2(jm2), damping(d), k(sc), aL(anchor)
{
	self.setOrigin(1.5f, 0.0f);
	self.setPosition(pos);
	self.setFillColor(sf::Color(0, 0, 0, 150));
}
void spring::rectRefresh(std::vector<std::vector<massPoint>> m) {

	
	sf::Vector2f diff = m[iM2][jM2].self.getPosition() - m[iM1][jM1].self.getPosition();
	sf::Vector2f d1 = diff / pythag(diff);
	float length = pythag(diff);

	float theta = atan(diff.y / diff.x) * 180.0f / 3.14159265358979f;
	if (m[iM2][jM2].self.getPosition().x >= m[iM1][jM1].self.getPosition().x) theta += 180.0f;


	self.setSize(sf::Vector2f(length, self.getOrigin().x * 2));
	self.setPosition(m[iM2][jM2].self.getPosition());
	self.setRotation(theta);
}