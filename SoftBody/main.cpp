#include "functions.h"


int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Soft Bodies", sf::Style::Default);

	int w = 5;
	int h = 5;
	int N = w * h;

	float damping = 0.99f;
	float springConstant = 0.001f;
	float anchorLength = 50.0f;

	sf::Vector2f currPos(300.0f, 300.0f);

	std::vector<massPoint> massPoints;

	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++) {
			massPoints.push_back(massPoint(1.0f, 0.01f, currPos));
			currPos.x += anchorLength;
		}

		currPos.x = 300.0f;
		currPos.y += anchorLength;
	}

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.clear(sf::Color::White);

		for (auto& x : massPoints)window.draw(x.self);

		window.display();
	}

	return 0;
}