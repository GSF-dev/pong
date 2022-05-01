#include <iostream>
#include <stdlib.h>
#include<time.h>
#include <conio.h>
#include <string>

//borders
#define BORDER_RIGHT 33
#define BORDER_LEFT 0
#define BORDER_TOP 0
#define BORDER_BOT 23
#define CENTRX BORDER_RIGHT/2
#define CENTRY BORDER_BOT/2


using namespace std;
int arr[BORDER_BOT + 1][BORDER_RIGHT + 1];

//Ball start position
struct ball {
	int X = CENTRX;
	int Y = CENTRY;
};
//rockets position
struct player {
	string name;
	int points;
	int X;
	struct Y
	{
		int top = CENTRY - 1;
		int mid = CENTRY;
		int bot = CENTRY + 1;
	}body;
}p1, p2;

//Variables
int ch;
bool quit, startGame;
ball ballPos;
player playerPos;

//Ball move direction
enum ballDirection { UPRIGHT, RIGHT, DOWNRIGHT, DOWNLEFT, LEFT, UPLEFT };
ballDirection direction;

//func
void startBallDirection();//chose random direction
void frame(ball& ball, player& pp);//draw frame
void reset(ball& ball, player& pp);//reset ball
void menu();
void input();
void ball_logic(ball& ball, player& pp);
void action();
void names();

//main
int main() {
	menu();
	names();
	startBallDirection();
	action();

	return 0;
}

//settings
void settings() {
	p1.points = 0;
	p2.points = 0;
	quit = false;
	startGame = true;
}
//randomise start ball direction
void startBallDirection() {
	srand(time(NULL));
	direction = (ballDirection)(rand() % 5);
}

//draw field, ball and rockets
void frame(ball& ball, player& pp) {
	system("cls");
	for (int i = BORDER_TOP; i <= BORDER_BOT; i++) {
		for (int j = BORDER_LEFT; j <= BORDER_RIGHT; j++) {
			//field
			if (i == BORDER_TOP || i == BORDER_BOT)
				cout << " ~ ";
			else
				if (j == BORDER_LEFT || j == BORDER_RIGHT)
					cout << " | ";
				else
					if (j == CENTRX && i > BORDER_TOP && i < BORDER_BOT)
						cout << " | ";
			//ball
					else
						if (j == ball.X && i == ball.Y)
							cout << " O ";
			//score	
						else
							if (j == BORDER_RIGHT / 4 && i == BORDER_TOP + 2) {
								if (p1.points < 10)
									cout << " " << p1.points << " ";
								else
									if (p1.points > 9)
										cout << " " << p1.points;
							}
							else
								if (j == BORDER_RIGHT / 4 * 3 && i == BORDER_TOP + 2)
									cout << " " << p2.points << " ";
			//rockets                 rocket 1
								else if (j == p1.X && i == p1.body.top) cout << " | ";
								else if (j == p1.X && i == p1.body.mid) cout << " | ";
								else if (j == p1.X && i == p1.body.bot) cout << " | ";
			//rocket 2
								else if (j == p2.X && i == p2.body.top) cout << " | ";
								else if (j == p2.X && i == p2.body.mid) cout << " | ";
								else if (j == p2.X && i == p2.body.bot) cout << " | ";
								else
									cout << "   ";
			if (j == BORDER_RIGHT)
				cout << endl;

		}
	}
}

void reset(ball& ball, player& pp)
{
	startGame = true;
	ball.X = CENTRX;
	ball.Y = CENTRY;
	p1.X = BORDER_LEFT + 2;
	p2.X = BORDER_RIGHT - 2;
	p1.body = { CENTRY - 1, CENTRY, CENTRY + 1 };
	p2.body = { CENTRY - 1, CENTRY, CENTRY + 1 };
}

void menu()
{
	cout << "   PONG   " << endl;
	cout << "1.NEW GAME" << endl;
	cout << "2.HIGH SCORE" << endl;
	cout << "   QUIT" << endl;
	ch = _getch();
	switch (ch)
	{
	case '1':break;
	case '2': break;
	default:
		break;
	}
}


//player input
void input() {
	if (_kbhit()) {
		ch = _getch();
		switch (ch) {
		case'w':
			if (p1.body.top != 2) {
				p1.X = BORDER_LEFT+2;
				p1.body.top -= 1;
				p1.body.mid -= 1;
				p1.body.bot -= 1;
			}
			break;
		case 's':
			if (p1.body.bot != BORDER_BOT - 2) {
				p1.X = BORDER_LEFT+2;
				p1.body.top += 1;
				p1.body.mid += 1;
				p1.body.bot += 1;
			}
			break;
		case 'i':
			if (p2.body.top != 2) {
				p2.X = BORDER_RIGHT - 2;
				p2.body.top -= 1;
				p2.body.mid -= 1;
				p2.body.bot -= 1;
			}
			break;
		case 'k':
			if (p2.body.bot != BORDER_BOT - 2) {
				p2.X = BORDER_RIGHT - 2;
				p2.body.top += 1;
				p2.body.mid += 1;
				p2.body.bot += 1;
			}
			break;
		case 'q':
			quit = true;
			break;
		}
	}
}

void ball_logic(ball& ball, player& pp) {
	switch (direction) {   //ball movement 
	case LEFT:
		ball.X--;
		break;
	case RIGHT:
		ball.X++;
		break;
	case UPLEFT:
		ball.X--;
		ball.Y--;
		break;
	case DOWNLEFT:
		ball.X--;
		ball.Y++;
		break;
	case UPRIGHT:
		ball.X++;
		ball.Y--;
		break;
	case DOWNRIGHT:
		ball.X++;
		ball.Y++;
		break;
	default:
		break;
	}
	if (ball.X == BORDER_RIGHT) {
		p1.points++;
		reset(ball, playerPos);
		startBallDirection();
	}
	else
		if (ball.X == BORDER_LEFT) {
			p2.points++;
			reset(ball, playerPos);
			startBallDirection();
		}
	//wall bounce

	if (ball.Y == BORDER_TOP + 1 && direction == UPLEFT)
		direction = DOWNLEFT;
	else //wall bounce
		if (ball.Y == BORDER_TOP + 1 && direction == UPRIGHT)
			direction = DOWNRIGHT;
		else //wall bounce
			if (ball.Y == BORDER_BOT - 1 && direction == DOWNLEFT)
				direction = UPLEFT;
			else //wall bounce
				if (ball.Y == BORDER_BOT - 1 && direction == DOWNRIGHT)
					direction = UPRIGHT;
	//rocket bounce

	if (ball.X == p1.X && ball.Y == p1.body.mid)
		direction = RIGHT;
	else
		if (ball.X == p1.X && ball.Y == p1.body.top)
			direction = UPRIGHT;
		else
			if (ball.X == p1.X && ball.Y == p1.body.bot)
				direction = DOWNRIGHT;
			else
				if (ball.X == p2.X && ball.Y == p2.body.mid)
					direction = LEFT;
				else
					if (ball.X == p2.X && ball.Y == p2.body.top)
						direction = UPLEFT;
					else
						if (ball.X == p2.X && ball.Y == p2.body.bot)
							direction == DOWNLEFT;
	startGame = false;
}

void action()
{
	while (!quit) {
		frame(ballPos, playerPos);
		input();
		ball_logic(ballPos, playerPos);
	}
	cout << p1.name << ": " << p1.points << "		" << p2.name << ": " << p2.points;
}
void names() {
	cout << "Type player 1 name: ";
	getline(cin, p1.name);
	cout << endl;
	cout << "Type player 2 name: ";
	getline(cin, p2.name);
}
