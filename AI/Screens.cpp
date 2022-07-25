#include "Screens.h"


Screens::Screens(sf::RenderWindow& window, int turn) : turn(turn), window(window), board(window)
{
	screen_sel = start;
	player.setRadius(45);
	turn = 1;
	player.setFillColor(sf::Color::Red);
	cover.setFillColor(sf::Color::Black);
	cover.setSize(sf::Vector2f(850, 100));
	cover.setPosition(0,0);
	select();
}


void Screens::TEXT(sf::Text& text, sf::Font& font, sf::Color color, int charSize) const {
	text.setFont(font);
	text.setFillColor(color);
	text.setCharacterSize(charSize);
	sf::FloatRect location = text.getLocalBounds();
	text.setOrigin(location.width / 2, 0);
}

void Screens::select() {
	switch (screen_sel)
	{
		case start: Home();
		case play: connect4();
		case end: end_screen();
	}
}

void Screens::reset() {
	turn = 1;
	board.reset();
}



void Screens::Home()  {
	window.clear(sf::Color::Black);
	reset();
	//retrieving font from file for text
	sf::Font font;
	font.loadFromFile("font/Roboto-Bold.ttf");

	//text for home screen
	sf::Text title, instruct, easy, medium, hard;
	title.setString("Connect 4");
	instruct.setString("Press one, two or three on keyboard");
	easy.setString("1: EASY");
	medium.setString("2: MEDIUM");
	hard.setString("3: HARD");

	TEXT(title, font, sf::Color::White, 50);
	title.setPosition(window.getSize().x / 2, 0);
	window.draw(title);
	TEXT(medium, font, sf::Color::White, 28);
	medium.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(medium);
	TEXT(instruct, font, sf::Color::White, 32);
	instruct.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 8 * medium.getLocalBounds().height);
	window.draw(instruct);
	TEXT(easy, font, sf::Color::White, 28);
	easy.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 4 * medium.getLocalBounds().height);
	window.draw(easy);
	TEXT(hard, font, sf::Color::White, 28);
	hard.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 4 * medium.getLocalBounds().height);
	window.draw(hard);
	window.display();
	while (window.isOpen()) {
		sf::Event choose;
		while (window.pollEvent(choose)) {
			if (choose.type == sf::Event::Closed)
			{
				window.close();
			}
			if (choose.type == sf::Event::KeyPressed && choose.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (choose.type == sf::Event::KeyPressed && (choose.key.code == sf::Keyboard::Num1))
			{
				window.clear();
				screen_sel = play;
				depth = 4;
				select();
				break;
			}
			else if (choose.type == sf::Event::KeyPressed && (choose.key.code == sf::Keyboard::Num2))
			{
				window.clear();
				screen_sel = play;
				depth = 6;
				select();
				break;
			}
			else if (choose.type == sf::Event::KeyPressed && (choose.key.code == sf::Keyboard::Num3))
			{
				window.clear();
				screen_sel = play;
				depth = 8;
				select();
				break;
			}
		}
	}
	window.clear();
	depth = 6;
}

void Screens::connect4() {
	Computer AI(depth);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				col = mouse.x / (window.getSize().x / 7);
				int play = pick_turn();
				row = board.get_pos(col);
				if (board.full(col) == false)
				{
					board.drop(row, col, play);
					turn++;
				}
				board.render();
				window.display();
				if (board.won(1))
				{
					screen_sel = end;
					select();
					break;
				}
				//AI moves
				play = pick_turn();
				col = AI.ai_play(board,4,play);
				row = board.get_pos(col);
				board.drop(row, col, play);
				if (board.won(2) || turn == 42)
				{
					screen_sel = end;
					break;
					select();
				}
				turn++;
			}
			window.draw(cover);
			board.render();
			hover(mouse);
			window.display();

		}
		if (screen_sel != play)
		{
			select();
			break;
		}
	}
}

int Screens::pick_turn() {
	if (turn % 2 == 1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}


void Screens::hover(sf::Vector2i mouse) {
	player.setPosition(mouse.x -25, 10);
	window.draw(player);
}

void Screens::end_screen() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			sf::Text winner, reset;
			sf::Font font;
			board.render();
			window.display();
			font.loadFromFile("font/Roboto-Bold.ttf");
			sf::Color colour;
			if (board.won(1))
			{
				winner.setString("You won");
				colour = sf::Color::Red;
			}
			if (board.won(2))
			{
				colour = sf::Color::Yellow;
				winner.setString("AI won");
			}
			TEXT(winner, font, colour, 32);
			winner.setPosition(window.getSize().x / 2, 0);
			window.draw(winner);

			reset.setString("Press enter to play again");
			TEXT(reset, font, sf::Color::White, 24);
			reset.setPosition(window.getSize().x / 2, winner.getLocalBounds().height + window.getSize().y / 120);
			window.draw(reset);
			window.display();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				screen_sel = start;
				select();
				break;
			}
		}
	}
}
