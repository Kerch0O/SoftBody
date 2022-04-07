#include "functions.h"


spring::spring(massPoint &p11, massPoint &p21, sf::Vector2f pos, float d, float sc, float anchor)
	: p1(p11), p2(p21), damping(d), k(sc), aL(anchor)
{
	self.setOrigin(1.5f, 0.0f);
	self.setPosition(pos);
	self.setOutlineColor(sf::Color::Black);
	self.setOutlineThickness(1);
	self.setFillColor(sf::Color(200, 200, 200));
}

void spring::rectRefresh(std::vector<std::vector<massPoint>> m) {

	
	sf::Vector2f diff = p2.self.getPosition() - p1.self.getPosition();
	sf::Vector2f d1 = diff / pythag(diff);
	float length = pythag(diff);

	float theta = atan(diff.y / diff.x) * 180.0f / 3.14159265358979f;
	if (p2.self.getPosition().x >= p1.self.getPosition().x) theta += 180.0f;


	self.setSize(sf::Vector2f(length, self.getOrigin().x * 2));
	self.setPosition(p2.self.getPosition());
	self.setRotation(theta);
}

void spring::physics(std::vector<std::vector<massPoint>>& m, float dt) {
	//Account for both the forces on each mass point as the two reverse forces along the string
	//First calculate seperately
	//Try just reversing one of them after

	//Account for gravity
	//Use semi-implicit euler integration, similar to verlet in stability, and the accuracy from Runge-Kutta with any order is not needed, so 
	//the simple SI-euler is best

	sf::Vector2f d = p2.self.getPosition() - p1.self.getPosition();
	//Make absolute
	d.x = d.x < 0 ? d.x * -1 : d.x;
	d.y = d.y < 0 ? d.y * -1 : d.y;

	float zeta = atan(d.x / d.y);
	float l = pythag(d);

	float Fs = -k * (l - aL); //Hooke's law

	sf::Vector2f a(1.0f, 1.0f);
	if (p2.self.getPosition().x > p1.self.getPosition().x) {
		a.x *= -1.0f;
	}
	if (p2.self.getPosition().y > p1.self.getPosition().y) {
		a.y *= -1.0f;
	}

	sf::Vector2f F1(Fs * sin(zeta), Fs * cos(zeta));
	F1 = F1 * a;

	//Negative means going towards p1

	//Handle damping force
	//Damping force is relevant to the velocities of the two points attatched
	//Negative when they are moving away
	//Positive when moving towards
	//So we use the dot product
	sf::Vector2f normalisedDistance = p2.self.getPosition() - p1.self.getPosition();
	normalisedDistance /= pythag(normalisedDistance);//Normalise
	float Fd = dot(normalisedDistance, p2.velocity - p1.velocity) * damping;

	F1 += Fd * normalisedDistance; //Apply force


	//First point:
	//F = ma, a = F/m
	sf::Vector2f acceleration = (sf::Vector2f(F1.x, F1.y)) / p1.m;
	p1.velocity += acceleration * dt;
	p1.self.move(p1.velocity * dt);

	

	//Second point
	acceleration = (sf::Vector2f(-F1.x, -F1.y)) / p2.m;
	p2.velocity += acceleration * dt;
	p2.self.move(p2.velocity * dt);
}