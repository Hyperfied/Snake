#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

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
};

Int2D direction = Int2D(0, 0);

std::vector<Int2D> initPlayer()
{
	std::vector<Int2D> playerPos;
	Int2D startPos = { boardWidth / 2, boardHeight / 2 };
	playerPos.push_back(startPos);
	return playerPos;
}

void ClearConsole()
{
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}

void displayBoard(std::vector<Int2D> &playerPos)
{
	ClearConsole();
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

void UpdatePlayer(std::vector<Int2D> &playerPos)
{
	GetKeyboardInput();
	Int2D newPos = playerPos.back() + direction;
	playerPos.push_back(newPos);
	playerPos.erase(playerPos.begin());
}

int main()
{
	std::vector<Int2D> playerPos = initPlayer();
	while (true)
	{
		displayBoard(playerPos);
		Sleep(updateDelay);
		UpdatePlayer(playerPos);
	}
}