#ifndef COMPUTER
#define COMPUTER

#include "Board.h"

class Computer
{
public:
	Computer(int setdepth);
	int scoremove(vector<vector<int>> board,int player);
	int ai_play(Board& board, int depth, int player);
private:
	int  depth;
	vector<int> possiblemoves;
	int score_vec(vector<int> vec, int player);
	int minimax(Board& board, int depth, int alpha, int beta, int player);
	int max(Board& board, int depth, int alpha, int beta, int player);
	int min(Board& board, int depth, int alpha, int beta, int player);
	void get_moves(Board& board);
	bool terminal(Board& board, int player);
};

#endif