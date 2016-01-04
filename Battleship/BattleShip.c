/*
 * Project: BattleShip
 * Created by CS106 Assignment Wizard 0.8
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <stdio.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"
#include "extgraph.h"
#include "random.h"
#include "sound.h"

#define NUM_COLS 15
#define NUM_ROWS 10
#define LG 0.3

typedef struct
{int row,col;}
coord;

typedef struct
{
	string name;
	int length;
	string color;
	string sound;
	int num;
} * class_p;

typedef struct
{
	string name;
	int clas;
	coord * contain;
} * ship_p;

string StartGame(void);
FILE * GetFile(void);
ship_p GetData(FILE *infile,class_p *class_p_p,ship_p *ship_p_p,int *ship_num_p);
void InitCell(ship_p cell[][NUM_COLS]);
void InitHistory(coord history[]);
void DrawStartingBoard(string choice);
void PlacingShips(class_p clas,ship_p ship,ship_p cell[][NUM_COLS],int ship_num);
void DrawScore(int MissilesLeft,int ShipsLeft,int hit,int total);
int percent(int hit,int total);
coord GetLocationChosenByUser(void);
void MarkMiss(coord location);
void MarkHit(coord location,string color,double density);
void MarkLineAsSunk(coord * contain,int length,string color);
bool IsInside(coord cell);
bool IsInHistory(coord location,coord history[]);
void PlayGame(coord history[],ship_p cell[][NUM_COLS],class_p clas,ship_p ship,int ship_num,string choice);
void DrawPrintfMessage(string message);

void main (void)
{
	FILE * infile;
	string choice;
	class_p clas;
	ship_p ship;
	ship_p cell[NUM_ROWS][NUM_COLS];
	int ship_num;
	coord history[100];

	Randomize();
	choice=StartGame();
	infile=GetFile();
	InitCell(cell);
	InitHistory(history);
	ship=GetData(infile,&clas,&ship,&ship_num);
	
	InitGraphics();
	DrawStartingBoard(choice);
	PlacingShips(clas,ship,cell,ship_num);
	

	PlayGame(history,cell,clas,ship,ship_num,choice);
}

string StartGame(void)
{
	string choice;
	printf("Welcome to the game of battleship!\n\n");
	printf("Want to play sound ? (y/n)  ");
	choice=GetLine();
	return choice;
}

FILE * GetFile(void)
{
	int num;
	string fname;
	num=RandomInteger(1,5);
	fname=Concat("ShipData",IntegerToString(num));
	return fopen(fname,"r");
}

ship_p GetData(FILE *infile,class_p *class_p_p,ship_p *ship_p_p,int *ship_num_p)
{
	int n,m,i,k;
	string clas;
	fscanf(infile,"Num Classes: %d\n",&n);
	*class_p_p=GetBlock( n * sizeof(**class_p_p));
	for (i=0;i<=n-1;i++)
	{
		(*class_p_p+i)->name=ReadLine(infile);
		(*class_p_p+i)->length=StringToInteger(ReadLine(infile));
		(*class_p_p+i)->color=ReadLine(infile);
		(*class_p_p+i)->sound=ReadLine(infile);
		(*class_p_p+i)->num=0;
		ReadLine(infile);
	}
	fscanf(infile,"Num Ships: %d\n",&m);
	*ship_num_p=m;
	*ship_p_p=GetBlock( m * sizeof(**ship_p_p));
	for (i=0;i<=m-1;i++)
	{
		(*ship_p_p+i)->name=ReadLine(infile);
		clas=ReadLine(infile);
		for (k=0;k<=n-1;k++)
		{
			if ( StringEqual( clas,(*class_p_p+k)->name ) )
			{
				(*ship_p_p+i)->clas=k;
				( (*class_p_p+k)->num )++;
				(*ship_p_p+i)->contain=GetBlock( (*class_p_p+k)->length * sizeof(coord) );
			}
		}
		ReadLine(infile);
	}
	return *ship_p_p;
}

void InitCell(ship_p cell[][NUM_COLS])
{
	int i,k;
	for (i=0;i<=NUM_ROWS-1;i++)
	{
		for (k=0;k<=NUM_COLS;k++)
		{
			cell[i][k]=NULL;
		}
	}
}

void InitHistory(coord history[])
{
	int i;
	for (i=0;i<=99;i++)
	{
		(history[i]).row=-1;
		(history[i]).col=-1;
	}
}

void DrawStartingBoard(string choice)
{
	int i;
	string letter[10]={"A","B","C","D","E","F","G","H","I","J"};
	if( StringEqual(choice,"y") ) { PlayNamedSound("Fanfare"); }
	for (i=0;i<=NUM_COLS;i++)
	{
		if (i!=NUM_COLS)
		{
			MovePen((i+1.3)*LG,GetWindowHeight()-LG);
			DrawTextString(IntegerToString(i));
		}
		MovePen((i+1)*LG,GetWindowHeight()-1.3*LG);
		DrawLine(0,(-NUM_ROWS)*LG);
	}
	for (i=0;i<=NUM_ROWS;i++)
	{
		if (i!=NUM_ROWS)
		{
			MovePen(LG/4,GetWindowHeight()-(11.1-i)*LG);
			DrawTextString(letter[9-i]);
		}
		MovePen(LG,GetWindowHeight()-(11.3-i)*LG);
		DrawLine((NUM_COLS)*LG,0);
	}
}

void PlacingShips(class_p clas,ship_p ship,ship_p cell[][NUM_COLS],int ship_num)
{
	coord CELL;
	int length,pass,col,row,i,k,j,direction;

	for(i=0;i<=ship_num-1;i++)
	{
		length=clas[ship[i].clas].length;
		do
		{
			col=RandomInteger(0,NUM_COLS);
			row=RandomInteger(0,NUM_ROWS);
			direction=RandomInteger(1,2);    // 1 for vert,2 for horiz
			pass=1;
			if (direction==1)
			{
				for (k=0;k<=length-1;k++)
				{
					CELL.col=col;
					CELL.row=row+k;
					if ( IsInside(CELL) && cell[CELL.row][CELL.col]==NULL )
					{;}
					else {pass=0;}
				}
			}
			if (direction==2)
			{
				for (k=0;k<=length-1;k++)
				{
					CELL.col=col+k;
					CELL.row=row;
					if ( IsInside(CELL) && cell[CELL.row][CELL.col]==NULL )
					{;}
					else {pass=0;}
				}
			}
		}
		while (pass==0);
		if (direction==1)
		{
			for (j=0;j<=length-1;j++)
			{
				cell[row+j][col]=&ship[i];
				( ( ship[i].contain )[j] ).row=row+j;
				( ( ship[i].contain )[j] ).col=col;
			}
		}
		if (direction==2)
		{
			for (j=0;j<=length-1;j++)
			{
				cell[row][col+j]=&ship[i];
				( ( ship[i].contain )[j] ).row=row;
				( ( ship[i].contain )[j] ).col=col+j;
			}
		}
	}
}

void DrawScore(int MissilesLeft,int ShipsLeft,int hit,int total)
{
	MovePen(16.5*LG,GetWindowHeight());
	StartFilledRegion(1);
	SetPenColor("White");
	DrawLine(0,-10*LG);
	DrawLine(7*LG,0);
	DrawLine(0,10*LG);
	DrawLine(-7*LG,0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(17*LG,GetWindowHeight()-4*LG);
	DrawTextString("Missiles left: ");
	DrawTextString(IntegerToString(MissilesLeft));
	MovePen(17*LG,GetWindowHeight()-5.5*LG);
	DrawTextString("Ships to sink: ");
	DrawTextString(IntegerToString(ShipsLeft));
	MovePen(17*LG,GetWindowHeight()-7*LG);
	DrawTextString("Hit rate: ");
	DrawTextString(IntegerToString(percent(hit,total)));
	DrawTextString("%");
}

int percent(int hit,int total)
{
	return (hit*100+0.0)/total-hit*100/total>=0.5 ? hit*100/total+1 : hit*100/total;
}

coord GetLocationChosenByUser(void)
{
	coord position;
	int i=0;
	double x,y;
	do
	{
		WaitForMouseDown();
		x=GetMouseX();
		y=GetMouseY();
		if (LG<x && x<16*LG && GetWindowHeight()-11.3*LG<y && y<GetWindowHeight()-1.3*LG)
		{
			i=1;
			for (i=16;i>=1;i--)
			{
				if (x>i*LG)
				{
					position.col=i-1;
					break;
				}
			}
			for (i=2;i<=12;i++)
			{
				if ((y-0.7*LG)>(GetWindowHeight()-i*LG))
				{
					position.row=i-3;
					break;
				}
			}
			return position;
		}
	}
	while (i==0);
}

void MarkMiss(coord location)
{
	MovePen( (location.col+1)*LG,GetWindowHeight()-(location.row+1.3)*LG );
	DrawLine(LG,-LG);
	MovePen( (location.col+2)*LG,GetWindowHeight()-(location.row+1.3)*LG );
	DrawLine(-LG,-LG);
}

void MarkHit(coord location,string color,double density)
{
	SetPenColor(color);
	MovePen( (location.col+1.5)*LG,GetWindowHeight()-(location.row+1.3)*LG );
	StartFilledRegion(density);
	DrawLine(-LG/2,-LG/2);
	DrawLine(LG/2,-LG/2);
	DrawLine(LG/2,LG/2);
	DrawLine(-LG/2,LG/2);
	EndFilledRegion();
	SetPenColor("Black");
}

void MarkLineAsSunk(coord * contain,int length,string color)
{
	int i;
	for (i=0;i<=length-1;i++)
	{
		MarkHit(contain[i],color,0.35);
	}
}

bool IsInside(coord cell)
{
	if ( 0<=cell.row && cell.row<=NUM_ROWS-1 && 0<=cell.col && cell.col<=NUM_COLS-1 )
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

bool IsInHistory(coord location,coord history[])
{
	int i;
	for (i=0;i<=99;i++)
	{
		if (location.row==history[i].row && location.col==history[i].col)
		{return TRUE;}
	}
	return FALSE;
}

void PlayGame(coord history[],ship_p cell[][NUM_COLS],class_p clas,ship_p ship,int ship_num,string choice)
{
	int num,hit=0,total=0,sum,length,q,sink=0,sink_this_time;
	string message;
	coord location;
	ship_p boat;
	DrawScore(100,ship_num,0,1);
	for (num=0;num<=99;num++)
	{
		do
		{
			location=GetLocationChosenByUser();
			if ( IsInHistory(location,history) )
			{;}
			else 
			{
				history[num].col=location.col;
				history[num].row=location.row;
				break;
			}
		}
		while(TRUE);
		
		total++;
		sink_this_time=0;
		if ( cell[location.row][location.col]==NULL )
		{			
			MarkMiss(location);
			DrawPrintfMessage("Miss!");
			if ( StringEqual("y",choice) ) { PlayNamedSound("Missile"); }
		}
		else
		{
			hit++;
			boat=cell[location.row][location.col];
			cell[location.row][location.col]=NULL;
			sum=0;
			length=clas[boat->clas].length;
			if( StringEqual(choice,"y") ) { PlayNamedSound( clas[boat->clas].sound ); }
			for (q=0;q<=length-1;q++)
			{
				if (cell[ (boat->contain)[q].row ][ (boat->contain)[q].col ]==NULL)
				{
					sum++;
				}
			}
			if (sum==length)
			{
				sink_this_time=1;
				sink++;
				clas[boat->clas].num--;
				MarkLineAsSunk( boat->contain,length,"White" );
				MarkLineAsSunk( boat->contain,length,clas[boat->clas].color );
				message="You sank the ";
				message=Concat(message,clas[boat->clas].name);
				message=Concat(message," ");
				message=Concat(message,boat->name);
				message=Concat(message," ! ");
				message=Concat(message,"There are ");
				message=Concat( message , IntegerToString(clas[boat->clas].num) );
				message=Concat(message," ");
				message=Concat(message,clas[boat->clas].name);
				message=Concat(message,"s left.");
				DrawPrintfMessage(message);
				if( StringEqual(choice,"y") ) { PlayNamedSound("You Sank My Battleship"); }
			}
			if (sink_this_time==0)
			{
				MarkHit(location,clas[boat->clas].color,0.85);
				DrawPrintfMessage("Direct hit!");
			}
		}
		DrawScore(99-num,ship_num-sink,hit,total);
		if (sink==ship_num)
		{
			break;
		}
	}
	if (sink==ship_num ) { DrawPrintfMessage("You win!"); }
	else { DrawPrintfMessage("I win!"); }
	if( StringEqual(choice,"y") )
	{
		if (sink==ship_num ) { PlayNamedSound("Song of Joy"); }
		else { PlayNamedSound("That's Pathetic"); }
	}
}

void DrawPrintfMessage(string message)
{
	MovePen( LG , GetWindowHeight()-11.5*LG );
	SetPenColor("White");
	StartFilledRegion(1);
	DrawLine(0,-2*LG);
	DrawLine(23*LG,0);
	DrawLine(0,2*LG);
	DrawLine(-23*LG,0);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen( 2*LG , GetWindowHeight()-12.3*LG );
	DrawTextString(message);
}



