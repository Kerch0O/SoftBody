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

	if (w >= 3 && h >= 3) {
		for (int i = 1; i < h - 1; i++) {
			for (int j = 1; j < w - 1; j++) {
				//Create spring in each direction straight and diagonal
				//8 total

				//Top Left
				springs.push_back(spring(i - 1, j - 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Top Middle
				springs.push_back(spring(i - 1, j, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Top Right
				springs.push_back(spring(i - 1, j + 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Middle Left
				springs.push_back(spring(i, j - 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Middle Right
				springs.push_back(spring(i, j + 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Bottom Left
				springs.push_back(spring(i + 1, j - 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Bottom Middle
				springs.push_back(spring(i + 1, j, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
				//Bottom Right
				springs.push_back(spring(i + 1, j + 1, i, j, massPoints[i][j].self.getPosition(), damping, springConstant, anchorLength));
			}
		}
	}
	else {
		std::cout << "Width and height parameters not allowed" << std::endl;
		window.close();
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

		for (auto& x : massPoints) {
			for (auto& y : x)window.draw(y.self);
		}

		window.display();
	}

	return 0;
}