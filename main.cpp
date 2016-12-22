#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

// class for ball object (creating game objects)

class cBall {
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY) {
		originalX = posX;
		originalX = posY;
		x = posX; 
		y = posY;
		direction = STOP;
	}
	void Reset() {
		x = originalX; 
		y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d) {
		direction = d;
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }
	void randomDirection() {
		direction = (eDir)((rand() % 6) + 1);
	}
	void Move() {
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case UPLEFT:
			y--; x--;
			break;
		case DOWNLEFT:
			y++; x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			y--; x++;
			break;
		case DOWNRIGHT:
			y++; x++;
			break;
		default:
			break;
		}
	}
	friend ostream & operator<<(ostream & o, cBall c) {
		o << "Ball [" << c.x << "," << c.y << "] [" << c.direction << "]" << endl;
		return o;
	}
};

// Class for player paddle objects (creating game objects)

class cPaddle {
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle() {
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle() {
		originalX = posX;
		originalY = posY;
		x = posX; 
		y = posY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }		// Get current x-position of the paddle
	inline int getY() { return y; }		// Get current y-position of the paddle
	inline void moveUp() { y--; }		// Move the paddle up by one block
	inline void moveDown() { y++; }		// Move the paddle down by one block
	friend ostream & operator<<(ostream & o, cPaddle c) {
		o << "Paddle [" << c.x << "," << c.y << "]" << endl;
		return o;
	}
};

// Class for managing the game

class cGameManager {
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall *ball;
	cPaddle *player1;
	cPaddle *player2;
public:

	// Constructor accepting dimensions of the gameplay

	cGameManager(int w, int h) {
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w/2, h/2);
		player1 = new cPaddle(1, (h / 2)-3);
		player2 = new cPaddle(w-2, (h / 2) - 3);
	}

	//De-contructor to delete dynamic memory allocated to objects: ensures no memory leaks

	~cGameManager() {
		delete ball, player1, player2;
	}

	//Function to increase player score : takes pointer to a player in memory as parameter

	void ScoreUp(cPaddle* player) {
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;
		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	// Funtion to draw elements on console screen

	void Draw() {
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player1y = player1->getY();
				int player2x = player2->getX();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2";
				if (ballx == j && bally == i)
					cout << "O";	//ball
				else if (player1x == j && player1y == i)
					cout << "\xDB";	//player1
				else if (player2x == j && player2y == i)
					cout << "\xDB";	//player2

														// Increasing paddle size for player1

				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB";	//player1
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB";	//player1
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB";	//player1

														// Increasing paddle size for player2

				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB";	//player1
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB";	//player1
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB";	//player1

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";

			}
			cout << endl;
		}
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Player 1: " << score1 << "\tPlayer 2: " << score1 << endl;
	}

	void Input() {
		ball->Move();

		// Get current position of objects
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		// Track for keyboard button to be hit
		if (_kbhit()) {
			char current = _getch();
			if (current == up1)
				if (player1y > 0)						// if player1 paddle is below the upper boundary of game frame, then
					player1->moveUp();					// move player1 paddle up
			if (current == up2)
				if (player2y > 0)						// if player paddle is below the upper boundary of game frame, then
					player2->moveUp();					// move player2 paddle up
			if (current == down1)
				if (player1y + 4 < height)				// if player1 paddle is above the lower boundary of game frame, then
					player1->moveDown();				// move player1 paddle down
			if (current == down2)
				if (player2y + 4 > 0)					// if player1 paddle is above the lower boundary of game frame, then
					player2->moveDown();				// move player paddle down
			if (ball->getDirection() == STOP)
				ball->randomDirection();
			if (current == 'q' || current == 'Q')		// if any of the players hit 'q' or 'Q', then
				quit = true;							// set quit = true, and Quit the game
		}
	}

	void Logic() {

		// Get current position of objects
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player1y = player1->getY();
		int player2x = player2->getX();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));
		}

		//right paddle
		for (int i = 0; i < 4; i++) {
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));
		}

		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		//upper wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPLEFT ? DOWNLEFT : DOWNRIGHT);

		//right wall
		if (ballx == width - 1)
			ScoreUp(player1);

		//left wall
		if (ballx == 0)
			ScoreUp(player2);
	}

	void Run() {
		while (!quit) {
			Draw();
			Input();
			Logic();
		}
	}
};
int main() {
	cGameManager c(40, 20);
	c.Run();
	Sleep(100);
	return 0;
}