#include <iostream>
#include <vector>
#include "VectorChar2D.h"

int boardWidth = 10;
int boardHeight = 10;

char boardChar = '-';
char playerChar = 'O';
char fruitChar = '#';

VectorChar2D initBoard()
{
	VectorChar2D board;

	for (int i = 0; i < boardHeight; i++)
	{
		std::vector<char> addVector;
		board.push_back(addVector);
		for (int j = 0; j < boardWidth; j++)
		{
			board[i].push_back(boardChar);
		}
	}

	return board;
}

void displayBoard(VectorChar2D board)
{
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}



int main()
{
	VectorChar2D board = initBoard();
	displayBoard(board);
}