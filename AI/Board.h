#ifndef BOARD
#define BOARD

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
using namespace std;

class Board {
public:
    // Constructor
    Board(sf::RenderWindow& screen);
    ~Board();
    void newgame(vector<vector<int>>& b);
    bool full(int col);
    int get_pos(int col);
    void drop(int row, int col, int player);
    void undo(int row, int col);
    bool won(int player);
    bool tie();
    vector< vector<int>> current();
    void render();
    void reset();
    sf::Color colour(int x, int y);

private:
    vector<vector<int>> game_board;
    sf::Color aicol = sf::Color::Yellow;
    sf::Color player = sf::Color::Red;
    sf::Color background = sf::Color::Black;
    sf::RectangleShape board;

    sf::RenderWindow& window;
    const int height =  6;
    const int width = 7;
    const int size = 45;
    int xgap;
    int ygap;

};


#endif