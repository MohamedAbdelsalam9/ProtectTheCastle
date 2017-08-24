#include <iostream>
#include <vector>
#include "enemy.h"
#include "tower.h"

using namespace std;

#include <windows.h>


#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3


// Some Datatypes definations
struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	//width
	int L;  //Height
};


/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);
/*A function to set the command window lenght and height for the game specification*/
void SetWindow();
/*A function to color the cmd text*/
void color(int thecolor);
/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(const castle & C);
/*A function to draw the castle and the towers*/
void DrawCastle(const castle & C,int SimulationTime, vector<tower> &towers);
/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(enemy& E, int Ypos=0);
/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(vector<enemy*> enemies);