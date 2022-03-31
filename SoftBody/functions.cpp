#include "functions.h"


void vCout(sf::Vector2f v, std::string s) {
	if (s.size() == 0) {
		std::cout << v.x << " " << v.y << std::endl;
	}
	else {
		std::cout << s << ": " << v.x << " " << v.y << std::endl;
	}

}
float pythag(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

void convAngle360(sf::Vector2f d, float& theta) {
	theta = d.x > 0.0f && d.y > 0.0f ? theta + 90.0f : theta;
	theta = d.x < 0.0f && d.y > 0.0f ? theta + 180.0f : theta;
	theta = d.x < 0.0f && d.y < 0.0f ? theta + 270.0f : theta;
}

sf::Vector2f operator*(sf::Vector2f v, sf::Vector2f k) {
	return sf::Vector2f(v.x * k.x, v.y * k.y);
}


void rectStep(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	for (auto& x : s)x.rectRefresh(m);
}

void physicsStep(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	for (auto& x : s)x.physics(m);
}

void pushStep(std::vector<std::vector<massPoint>>& m) {
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			m[i][j].selfColPush(m, sf::Vector2i(i, j));
		}
	}
}

void step(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	physicsStep(s, m);
	pushStep(m);
	rectStep(s, m);
}

void initialiseSprings(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, float d, float k, float a) {
	for (int i = 1; i < m.size();  i++) {
		for (int j = 0; j < m[i].size(); j++) {
			createPartition(m, s, i, j, d, k, a);
		}
	}
}

void createPartition(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, int i, int j, float d, float k, float a) {
	s.push_back(spring(m[i][j], m[i - 1][j], m[i][j].self.getPosition(), d, k, a));

	if (j < m[i].size() - 1) {
		s.push_back(spring(m[i][j], m[i][j + 1], m[i][j].self.getPosition(), d, k, a));
		s.push_back(spring(m[i][j], m[i - 1][j + 1], m[i][j].self.getPosition(), d, k, pythag(sf::Vector2f(a, a))));
		s.push_back(spring(m[i - 1][j], m[i - 1][j + 1], m[i - 1][j].self.getPosition(), d, k, a));
		s.push_back(spring(m[i - 1][j], m[i][j + 1], m[i - 1][j].self.getPosition(), d, k, pythag(sf::Vector2f(a, a))));
	}
}

bool circleCollision(sf::Vector2f p1, sf::Vector2f p2, float r) {
	float d = pythag(p1 - p2) - r;
	return d <= r && d != 0.0f;
}
void pushNormalR(massPoint& m1, massPoint& m2) {	

	float distance = pythag(m1.self.getPosition() - m2.self.getPosition());

	if (distance - m1.r < m2.r && distance != 0.0f) {
		//Inside-

		//Get normalised normal

		sf::Vector2f n = m2.self.getPosition() - m1.self.getPosition();
		float angle = atan(n.y / n.x);
		n = sf::Vector2f(cos(angle), sin(angle));

		if (m1.self.getPosition().x < m2.self.getPosition().x) {
			n.x *= -1.0f;
			n.y *= -1.0f;//Invert direction
		}

		//Get reflection velocity
		m1.velocity = m1.velocity - 2.0f * (dot(m1.velocity, n) / pow(pythag(n), 2)) * n;

		//Push circle out
		
		m1.self.setPosition(m2.self.getPosition() + n * (m2.r + m1.r));
	}
	
}

float dot(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

bool bounds(int i, int N) {
	return i != -1 && i < N;
}

float MAX(float a, float b) {
	return a > b ? a : b;
}
