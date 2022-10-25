#include <iostream>
#include <vector>
#include <algorithm>

int boardWidth = 10;
int boardHeight = 10;

char boardChar = '-';
char playerChar = 'O';
char fruitChar = '#';

struct Int2D
{
	int x, y;
	Int2D(int x, int y) {
		this->x = x;
		this->y = y;
	}
	bool operator==(const Int2D& b)
	{
		return (this->x == b.x) && (this->y == b.y);
	}
};


std::vector<Int2D> initPlayer()
{
	std::vector<Int2D> playerPos;
	Int2D startPos = { boardWidth / 2, boardHeight / 2 };
	playerPos.push_back(startPos);
	return playerPos;
}

void displayBoard(std::vector<Int2D> playerPos)
{
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (std::find(playerPos.begin(), playerPos.end(), Int2D(j, i)) != playerPos.end()) {
				std::cout << playerChar;
			}
			else
			{
				std::cout << boardChar;
			}
		}
		std::cout << std::endl;
	}
	
}

int main()
{
	std::vector<Int2D> playerPos = initPlayer();
	displayBoard(playerPos);
}