#include <iostream>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, speed = 100, speedcnt = 0;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void fruitLocation() {
	fruitX = rand() % width;
	if (fruitX == 0)
		fruitX += 1;
	fruitY = rand() % height;
	if (fruitY == 0)
		fruitY += 1;
}
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitLocation();
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == 0)							// Draw the top-left corner edge
				cout << "\xC9";
			else if (i == 0 && j == width - 1)				// Draw the top-right corner edge
				cout << "\xBB";
			else if (i == height - 1 && j == 0)				// Draw the bottom-left corner edge
				cout << "\xC8";
			else if (i == height - 1 && j == width - 1)		// Draw the bottom-right corner edge
				cout << "\xBC";
			else if ((i == 0) || (i == height - 1))			// Draw the top and bottom edge
				cout << "\xCD";
			else if ((j == 0) || (j == width - 1))			// Draw the side edges
				cout << "\xBA";
			else if ((i == y) && (j == x))					// Draw the snake head
				cout << "\x99";
			else if ((i == fruitY) && (j == fruitX))		// Draw the Snake's food
				cout << "\x40";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if ((tailX[k] == j) && (tailY[k] == i)) {
						cout << "o";					// Draw the Snake's tail
						print = true;
					}		
				}
				if (!print) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << endl << "Score : " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x >= width || x <= 0 || y >= height || y <= 0)
		//gameOver = true;

	if (x >= width) x = 1; if (x <= 0) x = width - 2;
	if (y >= height) y = 1; if (y <= 0) y = height - 2;
	for (int i = 1; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitLocation();
		nTail++;
		if (speedcnt == 3) {
			speed -= 5;
			speedcnt = 0;
		}
		else speedcnt++;
	}	
}
int main() {
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		if (speed <= 0)
			Sleep(0);
		else
			Sleep(speed);
	}
	return 0;
}