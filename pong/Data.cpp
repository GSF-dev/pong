#include "Data.h"

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
//put ball on centr
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

//game menu
void menu()
{
	do {
		system("cls");
		cout << "   PONG   " << endl;
		cout << "1.NEW GAME" << endl;
		cout << "2.MATCH RESULTS" << endl;
		cout << "   QUIT" << endl;
		ch = _getch();
		switch (ch) {
		case '1':system("cls"); break;
		case '2':system("cls");
			showResults(); break;
		case 'q': quit = true; break;
		default: system("cls");
			break;
		}
		cout << "Press any key to start new game!\n'R' - go back to menu.\n";
		ch = _getch();
	} while (ch == 'r');
}
//player input
void input() {
	if (_kbhit()) {
		ch = _getch();
		switch (ch) {
		case'w':
			if (p1.body.top != 2) {
				p1.X = BORDER_LEFT + 2;
				p1.body.top -= 1;
				p1.body.mid -= 1;
				p1.body.bot -= 1;
			}
			break;
		case 's':
			if (p1.body.bot != BORDER_BOT - 2) {
				p1.X = BORDER_LEFT + 2;
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
						if (ball.X == p2.X - 1 && ball.Y == p2.body.bot)
							direction == DOWNLEFT;
	startGame = false;
}
//the game
void action() {
	while (!quit) {
		frame(ballPos, playerPos);
		input();
		ball_logic(ballPos, playerPos);
		if (p1.points == 5 || p2.points == 5)
			quit = true;
	}
	system("cls");
	if (p1.points > p2.points)
		cout << p1.name << " WIN!!!" << endl;
	else
		cout << p2.name << " WIN!!!" << endl;
	cout << p1.name << ": " << p1.points << "	" << p2.name << ": " << p2.points << endl;
	writeResults();//record results in file

}
//registration names 
void names() {
	system("cls");
	cout << "Player 1: W - Up		Player 2: I - Up\n"
		"Player 2: S - Down		Player 2: K - Down\n\n";
	cout << "Type player 1 name: ";
	cin >> p1.name;
	cout << "Type player 2 name: ";
	cin >> p2.name;
	cout << endl;
}
//reading from file with results
void showResults()
{
	system("cls");
	fs.open("file.txt", ios::in);
	if (fs.is_open())
		while (!fs.eof()) {
			string str;
			getline(fs, str);
			cout << str << endl;
		}
	else
		cout << "File opening error\n";
	fs.close();
}
//record results in file
void writeResults()
{
	fs.open("file.txt", ios::app);
	if (fs.is_open())
		fs << p1.name << ": " << p1.points << "		" << p2.name << ": " << p2.points << endl;
	else
		cout << "File opening error\n";
	fs.close();
}