#include "Computer.h"
Computer::Computer(int setdepth): depth(setdepth) {

}

int Computer::ai_play(Board& board,int depth, int player) {
	return minimax(board,depth,-10000,10000,player);
}




int Computer::scoremove(vector<vector<int>> board, int player) {
	vector<int> vec;
	int movescore = 0;

	//horizontal 
	for (int i = 5 ; i > 0; i--) {
		for (int j = 0; j < 4; j++)
		{
			vec = { board[i][j],board[i][j + 1],board[i][j + 2],board[i][j + 3] };
			movescore += score_vec(vec, player);
		}
	}
	vec.clear();
	//vertical
	for (int i = 5; i > 2; i--) {
		for (int j = 0; j < 7; j++)
		{
			vec = { board[i][j],board[i-1][j],board[i-2][j],board[i-3][j] };
			movescore += score_vec(vec, player);
		}
	}
	//diagonal up
	vec.clear();
	for (int i = 5; i > 2; i--) {
		for (int j = 0; j < 4; j++)
		{
			vec = { board[i][j],board[i - 1][j+1],board[i - 2][j+2],board[i - 3][j+3] };
			movescore += score_vec(vec, player);
		}
	}
	vec.clear();
	//diagonal down
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++)
		{
			vec = { board[i][j],board[i + 1][j+1],board[i + 2][j+2],board[i + 3][j+3] };
			movescore += score_vec(vec, player);
		}
	}
	vec.clear();
	return movescore;
}


//heuristic function to score moves
int Computer::score_vec(vector<int> vec, int player) {
	int other = 1;
	int score = 0;
	if (player == other)
	{
		other = 2;
	}
	int counter = count(vec.begin(), vec.end(), player);
	int empty = count(vec.begin(), vec.end(), 0);
	int opponent = count(vec.begin(), vec.end(), other);
	if (counter == 4) {
		score += 100000;
	}
	else if (counter == 3 && empty == 1)
	{
		score += 500;
	}
	else if (counter == 2 && empty == 2)
	{
		score += 100;
	}
	else if (other == 4)
	{
		score -= 1000000;
	}
	else if (other == 3 && empty == 1)
	{
		score -= 500;
	}
	else if (other == 2 && empty == 2)
	{
		score -= 100;
	}
	return score;
}


void Computer::get_moves(Board& board) {
	possiblemoves.clear();
	for (int i = 0; i < 7; i++) {
		if (board.full(i) == false)
		{
			possiblemoves.push_back(i);
		}
	}
}



bool Computer::terminal(Board& board,int player) {
	if (board.won(player))
	{
		return true;
	} 
	else if (board.tie())
	{
		return true;
	}
	return false;
}

int Computer::minimax(Board& board, int depth, int alpha, int beta, int player) {
	get_moves(board);
	int col = 0;
	int best = -10000000;
	for (auto i : possiblemoves)
	{
		int row = board.get_pos(i);
		board.drop(row, i, player);
		int score = min(board, depth, alpha, beta, player);

		if (score > best)
		{
			best = score;
			alpha = score;
			col = i;
		}
		board.undo(row, i);
	}
	return col;
}

int Computer::max(Board& board, int depth, int alpha, int beta, int player) {
	if (terminal(board, player))
	{
		return -10000000;
	}
	if (depth <= 0)
	{
		return scoremove(board.current(), player);
	}
	get_moves(board);
	int best = -1000000;
	for (auto i : possiblemoves)
	{
		int row = board.get_pos(i);
		board.drop(row, i, player);
		player = 2;
		int score = min(board, depth - 1, alpha, beta, player);
		if (score > alpha)
		{
			alpha = score;
		}
		if (score > best)
		{
			best = score;
		}

		board.undo(row, i);
		if (alpha >= beta)
		{
			break;
		}
	}
	return best;
}

int Computer::min(Board& board, int depth, int alpha, int beta, int player) {
	if (terminal(board,player))
	{
		return 10000000;
	}
	if (depth <= 0)
	{
		return scoremove(board.current(), player);
	}
	get_moves(board);
	int best = 1000000;
	for (auto i : possiblemoves)
	{
		int row = board.get_pos(i);
		board.drop(row, i, player);
		player = 1;
		int score = max(board, depth-1, alpha, beta, player);
		if (score < beta)
		{
			beta = score;
		}
		if (score < best)
		{
			best = score;
		}

		board.undo(row, i);
		if (alpha >= beta)
		{
			break;
		}
	}
	return best;
}