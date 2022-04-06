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

void physicsStep(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m, float dt) {
	for (auto& x : s)x.physics(m, dt);
}

void collisionStep(std::vector<std::vector<massPoint>>& m, std::vector<Obstacle> &obstacles) {
	
	
	

	/*
	for (int i = 0; i < m.size(); i++) {
		if (m.size() % 2 == 0) {
			for (int j = 0; j < m[i].size(); j++) {
				
			}
		}
	}
	*/

	//Store reflections until after to actually reflect them

	std::vector<std::tuple<massPoint*, sf::Vector2f, sf::Vector2f>> reflections;

	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			m[i][j].selfColPush(m, sf::Vector2i(i, j), reflections);
		}
	}
	for (auto& x : reflections) {
		std::get<0>(x)->self.setPosition(std::get<2>(x));
		std::get<0>(x)->velocity = std::get<1>(x);
	}

	//This will check for collision with any surfaces or boundaries 
	for (auto& x : m)
		for (auto& y : x)boundaryPush(y, obstacles);
}



void step(std::vector<spring>& s, std::vector<std::vector<massPoint>>& m, std::vector<Obstacle> &obstacles, float dt) {
	physicsStep(s, m, dt);
	collisionStep(m, obstacles);
	rectStep(s, m);
}

void initialiseSprings(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, float d, float k, float a) {
	for (int i = 1; i < m.size();  i++) {
		for (int j = 0; j < m[i].size(); j++) {
			createPartition(m, s, i, j, d, k, a);
		}
	}

	for (int j = 0; j < m[0].size() - 1; j++) {

		s.push_back(spring(m[0][j], m[0][j + 1], m[0][j].self.getPosition(), d, k, a));
	}
}

void createPartition(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, int i, int j, float d, float k, float a) {
	s.push_back(spring(m[i][j], m[i - 1][j], m[i][j].self.getPosition(), d, k, a));

	if (j < m[i].size() - 1) {
		s.push_back(spring(m[i][j], m[i][j + 1], m[i][j].self.getPosition(), d, k, a));
		s.push_back(spring(m[i][j], m[i - 1][j + 1], m[i][j].self.getPosition(), d, k, pythag(sf::Vector2f(a, a))));
	//	s.push_back(spring(m[i - 1][j], m[i - 1][j + 1], m[i - 1][j].self.getPosition(), d, k, a));
		s.push_back(spring(m[i - 1][j], m[i][j + 1], m[i - 1][j].self.getPosition(), d, k, pythag(sf::Vector2f(a, a))));
	}
}

bool circleCollision(sf::Vector2f p1, sf::Vector2f p2, float r) {
	float d = pythag(p1 - p2) - r;
	return d <= r && d != 0.0f;
}

void pushNormalR(massPoint& m1, massPoint& m2, std::vector<std::tuple<massPoint*, sf::Vector2f, sf::Vector2f>> &reflections) {


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
		
		sf::Vector2f v = m1.velocity - 2.0f * (dot(m1.velocity, n) / pow(pythag(n), 2)) * n;
		v *= 0.5f;

		//Push circle out

		sf::Vector2f p(m2.self.getPosition() + n * (m2.r + m1.r));
		reflections.push_back(std::make_tuple(&m1, v, p));
	}
	
}

void boundaryPush(massPoint& m1, std::vector<Obstacle>& obstacles) {
	//Check if outside boundaries
	//Maybe some optimisations coukd be made here by just reversing velocities (check later)
	//Move and change normal dependant on the collision

	sf::Vector2f n(0.0f, 0.0f);
	bool collision = false;
	if (m1.self.getPosition().x - m1.r < 0.0f) {
		//Outside left
		n = sf::Vector2f(1.0f, 0.0f);
		m1.self.move(n * (0.0f - (m1.self.getPosition().x - m1.r)));
		collision = true;
	}
	else if (m1.self.getPosition().x + m1.r > 1200.0f) {
		//Outside right
		n = sf::Vector2f(-1.0f, 0.0f);
		m1.self.move(n * (m1.self.getPosition().x + m1.r - 1200.0f));
		collision = true;
	}
	//If statements for x and y are seperate because corners could have both
	if (m1.self.getPosition().y - m1.r < 0.0f) {
		//Outside top
		n = sf::Vector2f(0.0f, 1.0f);
		m1.self.move(n * (0.0f - (m1.self.getPosition().y - m1.r)));
		collision = true;
	}
	else if (m1.self.getPosition().y + m1.r > 800.0f) {
		//Outside bottom
		n = sf::Vector2f(0.0f, -1.0f);
		m1.self.move(n * (m1.self.getPosition().y + m1.r - 800.0f));
		collision = true;
	}
	//Obstacle Collision
	for (auto& x : obstacles) {
		sf::Vector2f closestP(-999.0f, -999.0f);
		if (rectCollision(m1.self.getPosition(), x.self) && obstaclePointIntersect(x, m1, closestP)) {
			//Run intersection step
			//^This just checks for bounding box intersection and then does the obstaclePointIntersect() if it is inside
			collision = true;

			n = closestP - m1.self.getPosition();
			float angle = atan(n.y / n.x);
			n = sf::Vector2f(cos(angle), sin(angle));

			m1.self.setPosition(closestP);
			std::cout << "Collision" << std::endl;
		}
	}

	if (collision)
		m1.velocity = m1.velocity - 2.0f * n * (dot(m1.velocity, n) / pow(pythag(n), 2));
}

bool obstaclePointIntersect(Obstacle& o, massPoint& m, sf::Vector2f& closest) {

	int intersections = 0;

	for (int i = 0, j = 1; i < o.ps.size(); i++, j++) {//This loop allows a point ahead and one behind
		j = j == 4 ? 0 : j;//So that it conforms to array size

		float grad = (o.ps[j].y - o.ps[i].y) / (o.ps[j].x - o.ps[i].x);//Get gradient of line + y intercept
		float yInte = -grad * o.ps[j].x + o.ps[j].y;

		float intersection = (m.self.getPosition().y - yInte) / grad;//Substitute in y value as a horizontal line into the line equation to get its intersect
		if (intersection < m.self.getPosition().x && intersection >= o.self.getGlobalBounds().left && intersection <= o.self.getGlobalBounds().left + o.self.getGlobalBounds().width){//Check if the intersect is valid
			intersections++;
		}

		//Find closest point

		float oGrad = -1.0f / grad;//Get orthogonal gradient and y intercept
		float oC = -oGrad * m.self.getPosition().x + m.self.getPosition().y;

		sf::Vector2f n;//Find intersection of the orthogonal line and the non-orthogonal line
		n.x = (oC - yInte) / (grad - oGrad);
		n.y = oGrad * n.x + oC;

		if (pythag(n - m.self.getPosition()) < pythag(closest - m.self.getPosition())) {//See if its closer out of all closest
			closest = n;
		}
	}

	return intersections % 2 != 0;//If the intersections are even, the point is outside, if odd, inside(this theory works in all situations, even with ones with holes)
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

float MIN(float a, float b) {
	return a < b ? a : b;
}

sf::Vector2f calcCorner(sf::Vector2f s, sf::Vector2f c, float r, int n) {
	sf::Vector2f p;
	switch (n) {
	case 1:
		p = c - s / 2.0f;
		break;
	case 2:
		p = sf::Vector2f(c.x + s.x / 2.0f, c.y - s.y / 2.0f);
		break;
	case 3:
		p = c + s / 2.0f;
		break;
	case 4:
		p = sf::Vector2f(c.x - s.x / 2.0f, c.y + s.y / 2.0f);
		break;
	}

	sf::Vector2f t = p - c;
	float PI = 3.14159265358979f;
	t = sf::Vector2f(t.x * cos(r * PI / 180.0f) - t.y * sin(r * PI / 180.0f), t.x * sin(r * PI / 180.0f) + t.y * cos(r * PI / 180.0f));
	return t + c;
}

bool rectCollision(sf::Vector2f p, sf::RectangleShape s) {
	return p.x > s.getGlobalBounds().left
		&& p.x < s.getGlobalBounds().left + s.getGlobalBounds().width
		&& p.y > s.getGlobalBounds().top
		&& p.y < s.getGlobalBounds().top + s.getGlobalBounds().height;
}

