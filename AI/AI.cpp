#include "Board.h"
#include "Screens.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(850, 850), "Connect 4", sf::Style::Close);
	window.setFramerateLimit(60);
	Screens game(window);
	return 0;
}