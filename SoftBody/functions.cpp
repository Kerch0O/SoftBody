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

void rectStep(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	for (auto& x : s)x.rectRefresh(m);
}

void physicsStep(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	
}
void step(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m) {
	physicsStep(s, m);
	rectStep(s, m);
}

float makeKey(float i, float j) {
	if (j > i)std::swap(i, j);//makes each input reversible and therefore will create the same result
	return (i + j) * (i + j + 1) / 2 + i; //Creates unique key based off of two integers(cantor pairing function)
}

void initialiseSprings(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, float d, float k, float a) {
	for (int i = 1; i < m.size();  i++) {
		for (int j = 0; j < m[i].size(); j++) {
			createPartition(m, s, i, j, d, k, a);
		}
	}
}

void createPartition(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, int i, int j, float d, float k, float a) {
	s.push_back(spring(i, j, i - 1, j, m[i][j].self.getPosition(), d, k, a));

	if (j < m[i].size() - 1) {
		s.push_back(spring(i, j, i, j + 1, m[i][j].self.getPosition(), d, k, a));
		s.push_back(spring(i, j, i - 1, j + 1, m[i][j].self.getPosition(), d, k, a));
		s.push_back(spring(i - 1, j, i - 1, j + 1, m[i - 1][j].self.getPosition(), d, k, a));
		s.push_back(spring(i - 1, j, i, j + 1, m[i - 1][j].self.getPosition(), d, k, a));
	}
}