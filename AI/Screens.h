#ifndef SCREENS
#define SCREENS

#include "Board.h"
#include "Computer.h"
#include <chrono>
#include <thread>

class Screens
{
	enum Mode { start, play, end };
public:
	Screens(sf::RenderWindow& window, int turn = 1);
	void Home();
private:
	Board board;
	sf::RenderWindow& window;
	int turn;
	int col;
	void hover(sf::Vector2i mouse);
	int depth;
	Mode screen_sel;
	void reset();
	void select();
	void connect4();
	int row;
	int pick_turn();
	sf::CircleShape player;
	sf::RectangleShape cover;
	void end_screen();
	void TEXT(sf::Text& text, sf::Font& font, sf::Color color, int size) const;
};

#endif