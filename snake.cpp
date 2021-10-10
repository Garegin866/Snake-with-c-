#include <iostream>
#include <conio.h>


using namespace std;

bool gameOver;
bool win;
const char* youWon = "You Won"; 
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;

void Setup() {
	gameOver = false;
	win = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls"); // maqruma terminaly
	for (int i = 0; i < width+1; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			if (!win) {

				if (i == y && j == x) {
					cout << "0";
				}
				else if (i == fruitY && j == fruitX) {
					cout << "f";
				}
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << 'o';
						}
					}
					if (!print)
						cout << ' ';
				}
			}
			else {
				int winPrint = false;
				if (i == height / 2 )
				{
					if (j == width / 2 - 4){
						cout << youWon;
					}
					else if (j < width-7){
						cout << "#";
					}
				}
				if (!(i == height / 2))
				{
					cout << " ";
				}
				gameOver = true;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width+1; i++) {
		cout << "#";
	}
	cout << endl;

	cout << "SCORE: " << score;

}

void Input() {

	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
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
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	

	if (x > width - 2 ){
		x = 0;
	}
	if (y > height - 1){
		y = 0;
	}
	if (x < 0) {
		x = width - 2;
	}
	if (y < 0) {
		y = height - 1;
	}
	for (int i = 0; i < nTail; i++){
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		nTail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
	if (score > 100){
		win = true;
	}
}


int main() {
	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	return 0;
}
