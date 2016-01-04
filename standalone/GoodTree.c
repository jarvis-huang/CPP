/*
 * Project: GoodTree
 * Created by CS106 Assignment Wizard 0.8
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"
#include "random.h"
#include "math.h"

#define rate 0.75            /*此常数指n+1级树枝与n级树枝长度之比*/
#define radian 3.1416/180    /*此常数将角度化成弧度*/

void Draw(double l,double sita);

void main(void)
{
	InitGraphics();
	Randomize();
	MovePen(3,0);
	DrawLine(0,1);
	Draw(1,0);
}

void Draw(double l,double sita)
{
	double x=GetCurrentX();
	double y=GetCurrentY();

	if ( RandomChance(0.95) ) 
	{
		
		if (l<=0.1) {return;}  
		/*This statement is used to end the program,otherwise it may run forever.*/
		
		DrawLine( rate*l*sin(sita-25*radian) , rate*l*cos(sita-25*radian) );
		Draw( rate*l,sita-25*radian );
	}

	if ( RandomChance(0.95) ) 
	{
		MovePen(x,y);
		/*This statement is to move pen to its original place,because it has been moved after the above statements.*/

		if (l<=0.1) {return;}
		DrawLine( rate*l*sin(sita+25*radian) , rate*l*cos(sita+25*radian) );
		Draw( rate*l,sita+25*radian );
	}
}




