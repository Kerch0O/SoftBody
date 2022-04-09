#include "functions.h"


//To Do:
//Maybe, maybe implement pressure based model

int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Soft Bodies", sf::Style::Default);

	//Structure
	int w = 5;
	int h = 3;
	int N = w * h;

	//Spring
	float damping = 10.0f;
	float springConstant = 1000.0f;
	float anchorLength = 20.0f;

	//Mass point
	float pointRadius = 6.67;
	float g = 100.0f;
	float pointMass = 1.0f;

	//Friction
	float frictionConstant = 0.02f; //0.01 - > Ice, 0.05->grippy, 0.03->~stone, 0.02->metal


	sf::Vector2f currPos(250.0f, 150.0f);

	std::vector<std::vector<massPoint>> massPoints;
	std::vector<spring> springs;

	//Clicking
	bool clicking = false;
	bool stepping = true;
	std::vector<std::vector<sf::Vector2f>> relPos;

	//FPS Counter
	sf::Text fps;
	fps.setCharacterSize(25);
	fps.setFillColor(sf::Color::Red);
	
	sf::Font calibri;
	calibri.loadFromFile("calibri.ttf");
	fps.setFont(calibri);
	fps.setString("");


	//Creating massPoint structure
	for (int i = 0; i < h; i++) {
		massPoints.push_back(std::vector<massPoint>());
		relPos.push_back(std::vector<sf::Vector2f>());

		for (int j = 0; j < w; j++) {
			massPoints[i].push_back(massPoint(pointMass, g, pointRadius, currPos));
			currPos.x += anchorLength;

			relPos[i].push_back(sf::Vector2f());
		}

		currPos.x = 250.0f;
		currPos.y += anchorLength;
	}


	//Creating springs
	initialiseSprings(massPoints, springs, damping, springConstant, anchorLength);

	//Obstacles
	std::vector<Obstacle> objects;
	objects.push_back(Obstacle(sf::Vector2f(225.0f, 400.0f), sf::Vector2f(75.0f, 200.0f), 330.0f));
	objects.push_back(Obstacle(sf::Vector2f(450.0f, 600.0f), sf::Vector2f(75.0f, 200.0f), 30.0f));
	objects.push_back(Obstacle(sf::Vector2f(700.0f, 400.0f), sf::Vector2f(30.0f, 200.0f), -156.0f));
	objects.push_back(Obstacle(sf::Vector2f(650.0f, 600.0f), sf::Vector2f(40.0f, 100.0f), 45.0f));
		
	//Delta Time
	sf::Clock fpsClock;
	float deltaTime = 1.0f / 60.0f;

	//Main Loop
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed: {

				sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				clicking = mouseMove(massPoints, mousePos);
				if (clicking) {
					std::cout << "Clicked Rect" << std::endl;
					for (int i = 0; i < massPoints.size(); i++) {
						for (int j = 0; j < massPoints[i].size(); j++) {
							relPos[i][j] = mousePos - massPoints[i][j].self.getPosition();
						}
					}
					stepping = false;
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
				clicking = false;
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

		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		if (clicking){
			
			for (int i = 0; i < massPoints.size(); i++) {
				for (int j = 0; j < massPoints[i].size(); j++) {
					sf::Vector2f d = mousePos - massPoints[i][j].self.getPosition();
					massPoints[i][j].self.move(d - relPos[i][j]);
				}
			}
			rectStep(springs, massPoints);
		}
		else{
			step(springs, massPoints, objects, deltaTime, frictionConstant);
		}
		
		
		window.clear(sf::Color(140, 140, 140));

		for (auto& x : objects)x.draw(window);

		for (auto x : springs)window.draw(x.self);

		for (auto& x : massPoints) {
			for (auto& y : x)window.draw(y.self);
		}

		window.draw(fps);


		window.display();

	}

	return 0;
}