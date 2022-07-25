
#include "Board.h"

Board::Board(sf::RenderWindow& screen) : window(screen)
{
	board.setFillColor(sf::Color::Blue);
	board.setPosition(0, 100);
	board.setSize(sf::Vector2f(screen.getSize().x, screen.getSize().y-100));
    xgap = board.getSize().x/width;
    ygap = board.getSize().y / height;
    newgame(game_board);
}
Board::~Board() {

};
void Board::newgame(vector<vector<int>>& b) {
    for (int i = 0; i < height; i++) { 
        // Vector to store column elements
        vector<int> v1;

        for (int j = 0; j < width; j++) {
            v1.push_back(0);
        }
        // Pushing back above 1D vector
        // to create the 2D vector
        b.push_back(v1);
    }
}

bool Board::full(int col) {
    return game_board[0][col] != 0;
}

vector< vector<int>> Board::current() {
    return game_board;
}

int Board::get_pos(int col) {
    for (int i = 5; i > 0; i--) {
        if (game_board[i][col] == 0)
        {
            return i;
        }
    }
}

void Board::drop(int row, int col, int player) {
    game_board[row][col] = player;
}

void Board::undo(int row, int col) {
    game_board[row][col] = 0;
}

bool Board::won(int player) {
    for (int i = height - 1; i > -1; i--) {
        for (int j = 0; j < width - 3; j++)
        {
            if (game_board[i][j] == player && game_board[i][j + 1] == player && game_board[i][j + 2] == player && game_board[i][j + 3] == player)
            {
                return true;
            }
        }
    }
    for (int i = height - 1; i > 2; i--) {
        for (int j = 0; j < width; j++)
        {
            if (game_board[i][j] == player && game_board[i - 1][j] == player && game_board[i - 2][j] == player && game_board[i - 3][j] == player)
            {
                return true;
            }
        }
    }
    for (int i = height - 1; i > 2; i--) {
        for (int j = 0; j < width - 3; j++)
        {
            if (game_board[i][j] == player && game_board[i - 1][j + 1] == player && game_board[i - 2][j + 2] == player && game_board[i - 3][j + 3] == player)
            {
                return true;
            }
        }
    }
    for (int i = 0; i < height - 3; i++) {
        for (int j = 0; j < width - 3; j++)
        {
            if (game_board[i][j] == player && game_board[i + 1][j + 1] == player && game_board[i + 2][j + 2] == player && game_board[i + 3][j + 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}


bool Board::tie() {
    vector<int> vec;
    for (int i = 0; i < 7; i++) {
        vec.push_back(game_board[0][i]);
    }
    int empty = count(vec.begin(), vec.end(), 0);
    if ( empty == 0)
    {
        return true;
    }
    return false;
}

void Board::render() {
    float x = 0;
    float y = board.getPosition().y + size * 2;
    sf::CircleShape piece;
    piece.setRadius(size);
    window.draw(board);
    for (int i = 0; i < height; i++)
    {
        y = ygap * i + 120;
        x = 0;
        for (int j = 0; j < width; j++)
        {
            x = xgap * j + 20;
            piece.setFillColor(colour(i, j));
            piece.setPosition(x, y);
            window.draw(piece);
        }
    }
    window.display();
}

sf::Color Board::colour(int x, int y) {
    if (game_board[x][y] == 0)
    {
        return background;
    }
    if (game_board[x][y] == 1)
    {
        return player;
    }
    if (game_board[x][y] == 2)
    {
        return aicol;
    }
}

void Board::reset() {
    for (int i = height - 1; i > -1; i--) {
        for (int j = 0; j < width; j++)
        {
            game_board[i][j] = 0;
        }
    }
}