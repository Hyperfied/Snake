#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <set>

int boardWidth = 10;
int boardHeight = 10;
int updateDelay = 500;

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
	Int2D operator+(const Int2D& b)
	{
		return Int2D(this->x + b.x, this->y + b.y);
	}
	bool operator!=(const Int2D& b)
	{
		return !(Int2D(this->x, this->y) == b);
	}
};

Int2D direction = Int2D(1, 0);
Int2D fruitPos = Int2D(0, 0);
Int2D textPos = Int2D(0, boardHeight);

std::vector<Int2D> initPlayer()
{
	std::vector<Int2D> playerPos;
	Int2D startPos = { boardWidth / 2, boardHeight / 2 };
	playerPos.push_back(startPos);
	return playerPos;
}

void initBoard(std::vector<Int2D> playerPos)
{
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (std::find(playerPos.begin(), playerPos.end(), Int2D(j, i)) != playerPos.end()) {
				std::cout << playerChar;
			}
			else if (fruitPos == Int2D(j, i))
			{
				std::cout << fruitChar;
			}
			else
			{
				std::cout << boardChar;
			}
		}
		std::cout << std::endl;
	}
}

void setCursorLocation(Int2D int2d)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)int2d.x, (SHORT)int2d.y };
	SetConsoleCursorPosition(hOut, coord);
}

void GetKeyboardInput()
{
	if (GetKeyState('A') & 0x8000)
	{
		direction = Int2D(-1, 0);
	}
	else if (GetKeyState('D') & 0x8000)
	{
		direction = Int2D(1, 0);
	}
	else if (GetKeyState('W') & 0x8000)
	{
		direction = Int2D(0, -1);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		direction = Int2D(0, 1);
	}
}

bool updatePlayer(std::vector<Int2D> &playerPos)
{
	Int2D newPos = playerPos.back() + direction;

	// Out of bounds / collide with self.

	if (newPos.x < 0 || newPos.x >= boardWidth || newPos.y < 0 || newPos.y >= boardHeight)
	{
		return true;
	}

	for (size_t i = 0; i < playerPos.size(); i++)
	{
		if (newPos == playerPos.at(i))
		{
			// Not unique! == collision
			return true;
		}
	}

	// Movement
	
	setCursorLocation(newPos);
	std::cout << playerChar;
	setCursorLocation(textPos);

	playerPos.push_back(newPos);

	if (newPos == fruitPos)
	{
		setCursorLocation(fruitPos);
		std::cout << playerChar;
		setCursorLocation(textPos);
		bool positionOccupied = true;
		while (positionOccupied)
		{
			positionOccupied = false;
			fruitPos = Int2D(rand() % boardWidth, rand() % boardHeight);
			for (size_t i = 0; i < playerPos.size(); i++)
			{
				if (fruitPos == playerPos.at(i)) {
					positionOccupied = true;
				}
			}
		}
		setCursorLocation(fruitPos);
		std::cout << fruitChar;
		setCursorLocation(textPos);
	}
	else
	{
		setCursorLocation(playerPos.at(0));
		std::cout << boardChar;
		setCursorLocation(textPos);
		playerPos.erase(playerPos.begin());
	}

	// Increase speed

	switch (playerPos.size())
	{
	case 5:
		updateDelay = 400;
		break;
	case 10:
		updateDelay = 300;
		break;
	case 15:
		updateDelay = 200;
		break;
	}

	return false;

	
}

int main()
{
	srand((unsigned)time(NULL));
	std::vector<Int2D> playerPos = initPlayer();

	initBoard(playerPos);

	// Main loop
	while (true)
	{
		Sleep(updateDelay/2);
		GetKeyboardInput();
		Sleep(updateDelay / 2);
		GetKeyboardInput();
		if (updatePlayer(playerPos))
		{
			break;
		}
	}
	setCursorLocation(textPos);
	std::cout << "You died!";
	Sleep(1000);
	std::cin;
}