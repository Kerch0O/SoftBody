#include "functions.h"

void testClick(std::vector<std::vector<massPoint>>& m, sf::RenderWindow& window) {
	sf::Vector2f mP = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			if (pythag(mP - m[i][j].self.getPosition()) <= m[i][j].self.getRadius()) {
				std::cout << "Mouse hit and clicked: " << i << " " << j << std::endl;
			}
		}
	}
}


int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Soft Bodies", sf::Style::Default);

	int w = 10;
	int h = 6;
	int N = w * h;

	float damping = 0.99f;
	float springConstant = 0.001f;
	float anchorLength = 50.0f;

	sf::Vector2f currPos(300.0f, 300.0f);

	std::vector<std::vector<massPoint>> massPoints;
	std::vector<spring> springs;

	for (int i = 0; i < h; i++) {
		massPoints.push_back(std::vector<massPoint>());
		for (int j = 0; j < w; j++) {
			massPoints[i].push_back(massPoint(1.0f, 0.01f, currPos));
			currPos.x += anchorLength;
		}

		currPos.x = 300.0f;
		currPos.y += anchorLength;
	}

	
	initialiseSprings(massPoints, springs, damping, springConstant, anchorLength);
		
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				testClick(massPoints, window);
			}
		}

		step(springs, massPoints);


		window.clear(sf::Color::White);

		for (auto x : springs)window.draw(x.self);

		for (auto& x : massPoints) {
			for (auto& y : x)window.draw(y.self);
		}

		window.display();
	}

	return 0;
}