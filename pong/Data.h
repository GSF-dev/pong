#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <fstream>


//borders
#define BORDER_RIGHT 33
#define BORDER_LEFT 0
#define BORDER_TOP 0
#define BORDER_BOT 23
#define CENTRX BORDER_RIGHT/2
#define CENTRY BORDER_BOT/2

using namespace std;

int arr[BORDER_BOT + 1][BORDER_RIGHT + 1];//field array

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
fstream fs;


//Ball move direction
enum ballDirection { UPRIGHT, RIGHT, DOWNRIGHT, DOWNLEFT, LEFT, UPLEFT };
ballDirection direction;

//func
void startBallDirection();//chose random direction
void frame(ball& ball, player& pp);//draw frame
void reset(ball& ball, player& pp);//reset ball
void menu();//game menu
void input();
void ball_logic(ball& ball, player& pp);
void action();
void names();
void showResults();
void writeResults();
