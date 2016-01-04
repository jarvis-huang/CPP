/* File: afterdark.c
 * -----------------
 * Replace this line with your name and your section leader's name.
 * ------------------
 * Replace this with your program comment.
 */
#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
#include "extgraph.h"
#include "random.h"
#include "sound.h"
#include "math.h"


/* General */
/* Use the height and width factors to be sure that both the 
 * graphics and console windows fit on your screen.  Adjust
 * the values as necessary.
 */

#define WINDOW_HEIGHT_FACTOR            0.55
#define WINDOW_WIDTH_FACTOR             0.90
#define NUM_COLORS                      16
#define PI                              3.1415926535

/* Constants for Shapes Screensaver */

#define MIN_SQUARE_WIDTH				0.5
#define MAX_SQUARE_WIDTH				1.5
#define MIN_SQUARE_HEIGHT				0.25
#define MAX_SQUARE_HEIGHT				1.0
#define MIN_CIRCLE_RADIUS               0.25
#define MAX_CIRCLE_RADIUS               0.75
#define MIN_TRIANGLE_BASE               0.5
#define MAX_TRIANGLE_BASE               1.25
#define MIN_TRIANGLE_HEIGHT             0.25
#define MAX_TRIANGLE_HEIGHT             2.0

/* Constants for Bouncing Ball Screensaver */

#define BALL_RADIUS                     0.25
#define MIN_DX                          0.03
#define MAX_DX                          0.05
#define MIN_DY                          0.03
#define MAX_DY                          0.05

/* Constants for Fireworks Screensaver */

#define MIN_FIREWORK_RADIUS				(MAX_FIREWORK_RADIUS / 2.0)
#define	MAX_FIREWORK_RADIUS				(GetWindowHeight() / 3.5)
#define MIN_NUM_SPOKES                  10
#define MAX_NUM_SPOKES                  20
#define PAUSE_BEFORE_FIRING             0.6
#define PAUSE_FOR_STREAM                0.02
#define PAUSE_BEFORE_EXPLOSION          0.3
#define NUM_STEPS_IN_EXPLOSION          20.0
#define NUM_STEPS_IN_STREAM             75.0
#define CHANCE_OF_COLOR_CHANGE          0.2

/* Constants for Images Screensaver */

#define NUM_RECT_WIDE                   5
#define NUM_RECT_HIGH                   4

/* My constants*/

#define CIRCLE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define PHRASE 4	

/* Function Prototypes */

void DefineColors (void);
string GetRandomColor (void);
void DrawPolarLine (double r, double theta);

/* Add your prototypes here. */

void menu(void);
void run(int choice);
void Shape();
void Bouncing_Ball();
void Fireworks();
void Images();
double Question1(void);
string Question2();
void DrawFilledCenteredCircle(double density);
void DrawFilledCenteredRectangle(double density);
void DrawFilledCenteredTriangle(double density);
void DrawPhrase(string phrase);
void DrawWindowBlack();
void DrawBall(double x,double y);
void shooting(double center_x,double center_y);
void expanding(double radius,int Num_Spokes);
void fading(double radius,int Num_Spokes);


main() 
{
	int choice;
	SetWindowSize(GetFullScreenWidth() * WINDOW_WIDTH_FACTOR, 
                  GetFullScreenHeight() * WINDOW_HEIGHT_FACTOR);
	InitGraphics();
	Randomize();
	DefineColors();
	
	/* Add your code here and in additional functions. */
	do
	{

		do
		{
			menu();
			choice=GetInteger();
			if (choice==0||1||2||3||4) 
			{
				break;
			}
			
		}
		while (choice!=0||1||2||3||4);
		if (choice!=0) run(choice);
		else break;
	}
	while (TRUE);
}

void DefineColors (void)
{
	DefineColor("Orange", 0.9, 0.5, 0);
	DefineColor("Gold", 0.9, 0.8, 0);
	DefineColor("Emerald", 0, 0.8, 0);
	DefineColor("Teal", 0, 0.8, 0.7);
	DefineColor("Aqua", 0, 0.6, 1.0);
	DefineColor("Periwinkle", 0.5, 0, 0.7);
	DefineColor("Purple", 0.6, 0, 0.7);
	DefineColor("Violet", 0.6, 0, 0.6);
	DefineColor("HotPink", 1.0, 0, 0.5);
}

string GetRandomColor (void)
{
	int color;
	
	color = RandomInteger(1, NUM_COLORS);
	
	switch (color) {
		case 1: return("Red");
		case 2: return("Orange");
		case 3: return("Gold");
		case 4: return("Yellow");
		case 5: return("Green");
		case 6: return("Emerald");
		case 7: return("Teal");
		case 8: return("Cyan");
		case 9: return("Aqua");
		case 10: return("Blue");		
		case 11: return("Periwinkle");
		case 12: return("Purple");
		case 13: return("Violet");	
		case 14: return("Magenta");
		case 15: return("HotPink");
		case 16: return("White");
	}
}


void DrawPolarLine (double r, double theta)
{
	double radians;
	
	radians = theta/180 * PI;
	DrawLine(r * cos(radians), r * sin(radians));	
}

void menu(void)
{
	printf("Which screensaver would you like to use?\n");
	printf("Enter 1 for Shapes.\n");
	printf("Enter 2 for Bouncing Ball.\n");
	printf("Enter 3 for Fireworks.\n");
	printf("Enter 4 for Images.\n");
	printf("Enter 0 to Quit.\n");
	printf("Your choice= ");
}
void run(choice)
{
	switch(choice)
	{
	case 1:Shape();
		   break;
	case 2:Bouncing_Ball();
		   break;
	case 3:Fireworks();
		   break;
	case 4:Images();
			break;
	}
	printf("\n");
}

void Shape(void)
{
	double density;
	string phrase;
	int shape;
	density=Question1()/10.0;
	phrase=Question2();
	while (!MouseButtonIsDown())
	{
		shape=RandomInteger(CIRCLE,PHRASE);
		switch(shape)
		{
			case CIRCLE:DrawFilledCenteredCircle(density);
			break;
			case RECTANGLE:DrawFilledCenteredRectangle(density);
			break;
			case TRIANGLE:DrawFilledCenteredTriangle(density);
			break;
			default:DrawPhrase(phrase);
		}
		Pause(0.2);
	}
}


double Question1(void)
{
	double density1;
	do
	{
		printf("How solidly colored shapes do you want?\n");
		printf("Enter a number between 1 and 10: ");
		density1=GetReal();
		if (density1>=1 && density1<=10) break;
	}
	while (TRUE);
	return (density1);
}

string Question2()
{
	string phrase1;
	printf("Enter your favorite phrase: ");
	phrase1=GetLine();
	return(phrase1);
}

void DrawFilledCenteredCircle(double density)
{
	double x,y,radius;
	x=RandomReal(0,GetWindowWidth());
	y=RandomReal(0,GetWindowHeight());
	MovePen(x,y);
	radius=RandomReal(MIN_CIRCLE_RADIUS,MAX_CIRCLE_RADIUS);
	SetPenColor(GetRandomColor());
	StartFilledRegion(density);
	DrawArc(radius,0,360);
	EndFilledRegion();
	UpdateDisplay();
}

void DrawFilledCenteredRectangle(double density)
{
	double x,y,width,height;
	x=RandomReal(0,GetWindowWidth());
	y=RandomReal(0,GetWindowHeight());
	MovePen(x,y);
	width=RandomReal(MIN_SQUARE_WIDTH,MAX_SQUARE_WIDTH);
	height=RandomReal(MIN_SQUARE_HEIGHT,MAX_SQUARE_HEIGHT);
	SetPenColor(GetRandomColor());
	StartFilledRegion(density);
	DrawLine(width,0);
	DrawLine(0,height);
	DrawLine(-width,0);
	DrawLine(0,-height);
	EndFilledRegion();
	UpdateDisplay();
}

void DrawFilledCenteredTriangle(double density)
{
	double x,y,base,height;
	x=RandomReal(0,GetWindowWidth());
	y=RandomReal(0,GetWindowHeight());
	MovePen(x,y);
	base=RandomReal(MIN_TRIANGLE_BASE,MAX_TRIANGLE_BASE);
	height=RandomReal(MIN_TRIANGLE_HEIGHT,MAX_TRIANGLE_HEIGHT);
	SetPenColor(GetRandomColor());
	StartFilledRegion(density);
	DrawLine(base,0);
	DrawLine(-base/2,height);
	DrawLine(-base/2,-height);
	DrawLine(0,-height);
	EndFilledRegion();
	UpdateDisplay();
}

void DrawPhrase(string phrase)
{
	double x,y;
	x=RandomReal(0,GetWindowWidth());
	y=RandomReal(0,GetWindowHeight());
	MovePen(x,y);
	SetPenColor(GetRandomColor());
	DrawTextString(phrase);
	UpdateDisplay();
}

void Bouncing_Ball(void)
{
	double x,y,dx,dy;
	DrawWindowBlack();
	SetPenColor(GetRandomColor());
	x=RandomReal(BALL_RADIUS,GetWindowWidth()-BALL_RADIUS);
	y=RandomReal(BALL_RADIUS,GetWindowHeight()-BALL_RADIUS);
	dx=RandomReal(MIN_DX,MAX_DX);
	dy=RandomReal(MIN_DY,MAX_DY);
	if (x>GetWindowWidth()-BALL_RADIUS)
	{
		dx=-dx;
	}
	if (y>GetWindowHeight()-BALL_RADIUS)
	{
		dy=-dy;
	}
	MovePen(x,y);
	DrawBall(x,y);
	x=x+dx;
	y=y+dy;
	MovePen(x,y);
	while (!MouseButtonIsDown())
	{
		if (x>0.25+GetWindowWidth()-BALL_RADIUS||x<0.25+BALL_RADIUS)
		{
			dx=-dx;
			SetPenColor(GetRandomColor());
		}
		if (y>GetWindowHeight()-BALL_RADIUS||y<BALL_RADIUS)
		{
			dy=-dy;
			SetPenColor(GetRandomColor());
		}
		DrawBall(x,y);
		x=x+dx;
		y=y+dy;
		MovePen(x,y);
	}
}

void DrawWindowBlack(void)
{
	MovePen(0,0);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawLine(GetWindowWidth(),0);
	DrawLine(0,GetWindowHeight());
	DrawLine(-GetWindowWidth(),0);
	DrawLine(0,-GetWindowHeight());
	EndFilledRegion();
	UpdateDisplay();
}

void DrawBall(double x,double y)
{
	string color;
	color=GetPenColor();
	StartFilledRegion(1);
	DrawArc(BALL_RADIUS,0,360);
	EndFilledRegion();
	UpdateDisplay();
	Pause(0.03);
	SetPenColor("Black");
	StartFilledRegion(1);
	DrawArc(BALL_RADIUS,0,360);
	EndFilledRegion();
	SetPenColor(color);
	
}

	void Fireworks(void)
{
	int Num_Spokes;
	double radius,center_x,center_y;
	DrawWindowBlack();
	Pause(PAUSE_BEFORE_FIRING);
	while (!MouseButtonIsDown())
	{
		Num_Spokes=RandomInteger(MIN_NUM_SPOKES,MAX_NUM_SPOKES);
		radius=RandomReal(MIN_FIREWORK_RADIUS,MAX_FIREWORK_RADIUS);
		center_x=RandomReal(radius,GetWindowWidth()-radius);
		center_y=RandomReal(GetWindowHeight()/2,GetWindowHeight()-radius);
		PlayNamedSound("Fire");
		MovePen(center_x,0);
		shooting(center_x,center_y);
		PlayNamedSound("Explode");
		Pause(PAUSE_BEFORE_EXPLOSION);
		expanding(radius,Num_Spokes);
		UpdateDisplay();
		fading(radius,Num_Spokes);
		}
}

void shooting(double center_x,double center_y)
{
	int i;
	string color;
	double length=center_y/NUM_STEPS_IN_STREAM;
	SetPenColor("White");
	color=GetPenColor();
	for (i=1;i<=NUM_STEPS_IN_STREAM;i=i+1)
	{
		DrawLine(0,length);
		UpdateDisplay();
		Pause(PAUSE_FOR_STREAM);
		SetPenColor("Black");
		DrawLine(0,-length);
		DrawLine(0,length);
		SetPenColor(color);
	}
}

void expanding(double radius, int Num_Spokes)
{
	int i,k;
	double length=radius/NUM_STEPS_IN_EXPLOSION;
	for(i=0;i<=Num_Spokes-1;i=i+1)
	{	
		for(k=1;k<=Num_Spokes;k=k+1)
		{
			DrawPolarLine(i*length,(k-1)*360/Num_Spokes);
			DrawPolarLine(i*length,180+(k-1)*360/Num_Spokes);
		}
	
		if (RandomChance(CHANCE_OF_COLOR_CHANGE))
		{
			SetPenColor(GetRandomColor());
		}
		Pause(PAUSE_FOR_STREAM);
	}
}

void fading(double radius,int Num_Spokes)
{
	int i,k;
	double length=radius/NUM_STEPS_IN_EXPLOSION;
	SetPenColor("Black");
	for(i=0;i<=Num_Spokes-1;i=i+1)
	{
		for(k=1;k<=Num_Spokes;k=k+1)
		{
			DrawPolarLine(i*length,(k-1)*360/Num_Spokes);
			DrawPolarLine(i*length,180+(k-1)*360/Num_Spokes);
		}
		Pause(PAUSE_FOR_STREAM);
	}
}

void Images()
{
	MovePen(2,1);
	SetPenColor("Black");
	
	DrawArc(1,0,360);
	
	UpdateDisplay();
	
}











