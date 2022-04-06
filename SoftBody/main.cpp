#include "functions.h"

sf::Vector2i testClick(std::vector<std::vector<massPoint>>& m, sf::RenderWindow& window) {
	sf::Vector2f mP = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			if (pythag(mP - m[i][j].self.getPosition()) <= m[i][j].self.getRadius()) {
				return sf::Vector2i(i, j);
			}
		}
	}

	return sf::Vector2i(-1, -1);
}


int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Soft Bodies", sf::Style::Default);
//	window.setFramerateLimit(60);
//	window.setVerticalSyncEnabled(false);

	int w = 5;
	int h = 3;
	int N = w * h;

	float damping = 0.98f;
	float springConstant = 2000.0f;
	float anchorLength = 20.0f;
	float pointRadius = 6.67;

	sf::Vector2f currPos(300.0f, 300.0f);

	std::vector<std::vector<massPoint>> massPoints;
	std::vector<spring> springs;

	sf::Vector2i currClicked(-1, -1);
	bool clicking = false;

	//FPS Counter
	sf::Text fps;
	fps.setCharacterSize(25);
	fps.setFillColor(sf::Color::Red);
	
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");
	fps.setFont(calibri);
	fps.setString("");


	for (int i = 0; i < h; i++) {
		massPoints.push_back(std::vector<massPoint>());
		for (int j = 0; j < w; j++) {
			massPoints[i].push_back(massPoint(1.0f, 700.0f, pointRadius, currPos));
			currPos.x += anchorLength;
		}

		currPos.x = 300.0f;
		currPos.y += anchorLength;
	}


	
	initialiseSprings(massPoints, springs, damping, springConstant, anchorLength);

	std::vector<Obstacle> objects;
//	objects.push_back(Obstacle(sf::Vector2f(275.0f, 600.0f), sf::Vector2f(75.0f, 200.0f), 330.0f));
		
	//Delta Time

	sf::Clock fpsClock;
	float deltaTime = 1.0f / 60.0f;

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				clicking = true;
				currClicked = testClick(massPoints, window);
				break;
			case sf::Event::MouseButtonReleased:
				clicking = false;
				currClicked = sf::Vector2i(-1, -1);
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode == 's') {
				//	step(springs, massPoints, objects, delta);
				}
				break;
			}
		}

		float deltaClockT = fpsClock.getElapsedTime().asSeconds();
		if (deltaClockT >= 0.007f) {
			deltaTime = 0.007f;
		}
		else {
			deltaTime = deltaClockT;
		}
		fpsClock.restart();
		fps.setString(std::to_string(1.0f / deltaClockT));


		if (clicking && currClicked.x != -1) {
			massPoints[currClicked.x][currClicked.y].self.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		}
		
		step(springs, massPoints, objects, deltaTime);
		
	


		window.clear(sf::Color::White);

		for (auto x : springs)window.draw(x.self);

		for (auto& x : massPoints) {
			for (auto& y : x)window.draw(y.self);
		}

		window.draw(fps);

		for (auto& x : objects)x.draw(window);

		window.display();

	}

	return 0;
}