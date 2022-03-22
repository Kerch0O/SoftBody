#include "functions.h"

int IX(int i, int j, int N) {
	return i + N * j;
}

void vCout(sf::Vector2f v, std::string s) {
	if (s.size() == 0) {
		std::cout << v.x << " " << v.y << std::endl;
	}
	else {
		std::cout << s << ": " << v.x << " " << v.y << std::endl;
	}

}