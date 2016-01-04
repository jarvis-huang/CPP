#include "genlib.h"
#include "simpio.h"
#include "geometry.h"
#include "species.h"
#include "world.h"
#include "worldmap.h"
#include "creature.h"
#include "random.h"
#include "strlib.h"
#include "symtab.h"
#include "extgraph.h"

#define NRows 15
#define NColumns 15
#define MaxSpecies 10
#define InitialCount 10
#define MaxCreatures 100
#define MaxProgram 250

#define InitialTimeInterval 0.0005

speciesADT *SetSpecies(int *numcreature);
speciesADT *Shuffle(speciesADT *old,int num);
void PrintInstructions1();
void PrintInstructions2();
void PlacingCreatures(worldADT world,creatureADT *creatureP,speciesADT *speciesP,int numcreature);
bool WantToContinue(creatureADT *creatureP,int num,double *time);
bool WantToPlayAgain();
void PrintInventory(string key,void *value,void *clientData);
void ChangeTimeInterval(double *time);


void main (void)
{

	worldADT world;
	int i;
	double time=InitialTimeInterval;
	int numcreature;
	speciesADT *speciesP;
	creatureADT *creatureP; 


	while(TRUE)
	{
		Randomize();
		InitGraphics();
		InitWorldMap(NColumns,NRows);
		i=0;
		numcreature=0;
	
		world=NewWorld(NColumns,NRows);
		PrintInstructions1();

		speciesP=SetSpecies(&numcreature);
		speciesP=Shuffle(speciesP,numcreature);
	
		creatureP=GetBlock( numcreature * sizeof (creatureADT) );
		PlacingCreatures(world,creatureP,speciesP,numcreature);
		
		PrintInstructions2();

		while ( !MouseButtonIsDown() || WantToContinue(creatureP,numcreature,&time) )
		{
			TakeOneTurn(creatureP[i]);
			i=(i+1)%numcreature;
			Pause(time);
		}
				
		FreeWorld(world);
		FreeBlock(creatureP);

		if (!WantToPlayAgain())  {break;}

	}
}

/*
	Function : PrintInstructions 
	------------------------------------
	This function is used to print some instructions to 
	tell the user how to play.
*/

void PrintInstructions1()
{
	printf("Welcome to the game of Darwin!\n");
	printf("Enter the name of species you want to include.\n");
	printf("To end the list,type a blank line.\n\n");
}

void PrintInstructions2()
{
	printf("\nThe Game is going to start . Press any key when you are ready.");
	GetLine();
	printf("\nTo pause,click mouse on the graph.\n");
}

/*
	Function : SetSpecies 
	----------------------------------
	This function is used to create an array holding 'speciesADT*'
	according to the user's input. Its size is the same as the 
	number of creatures because every item in this array corresponds
	to the species of a creature. This function reads species 
	from files.
*/

speciesADT *SetSpecies(int *numcreature)
{
	string str;
	int numspecies=0,k;
	speciesADT *speciesP=GetBlock( MaxCreatures * sizeof (speciesADT) );
	speciesADT species;
	FILE *infile;
	symtabADT symtab=NewSymbolTable();

	while (TRUE)
	{
		printf("Input a species name (Food,Hop,Flytrap,Rover,Loner):  ");
		str=GetLine();
		if (StringEqual (str,"") && *numcreature==0)
		{
			printf("No.You must at least enter one species!\n");
		}
		else if (StringEqual(str,"") && *numcreature!=0)
		{
			break;
		}
		else 
		{
			infile=fopen(Concat("Creatures\\", str),"r");
			if (infile==NULL)  {printf("No such data file.Try again.\n");}
			else 
			{
				species=ReadSpecies(str);
				if (Lookup(symtab,SpeciesName(species))==UNDEFINED)
				{
					printf("%s ",SpeciesName(species));
					numspecies++;
					Enter (symtab,SpeciesName(species),species);
				}
				fclose(infile);
				for (k=*numcreature ; k<=*numcreature+9 ; k++)
				{
					speciesP[k]=species;
				}
				*numcreature = *numcreature + 10 ;
				if (*numcreature==MaxCreatures || numspecies==MaxSpecies)  { break; }
			}
		}
	}
	return speciesP;
}
		
/*
	Function : Shuffle
	---------------------------------
	This function shuffle the array created by SetSpecies and 
	return it. We shuffle the array because we should give every
	creature equal chance to take turn. For example, it is not
	allowed that all 'Flytrap' take turn first and then for the
	'Rover'.
*/

speciesADT *Shuffle(speciesADT *old,int num)
{
	int k,m,j;
	speciesADT *New = GetBlock ( num * sizeof (speciesADT) );

	for (k=0;k<=num-1;k++)
	{
		m=RandomInteger(0,num-k-1);
		New[k]=old[m];
		for (j=m;j<=num-k-2;j++)
		{
			old[j]=old[j+1];
		}
	}
	
	return New;
}

/*
	Function : PlacingCreatures
	--------------------------------------
	This function just place the creatures on the world map 
	randomly.
*/

void PlacingCreatures(worldADT world,creatureADT *creatureP,speciesADT *speciesP,int numcreature)
{
	int i;
	pointT pt;

	for (i=0;i<=numcreature-1;i++)
	{
		while(TRUE)
		{
			pt.x=RandomInteger(0,WorldWidth(world)-1);
			pt.y=RandomInteger(0,WorldHeight(world)-1);
			if ( GetContents(world,pt) == NULL )
			{
				creatureP[i]=NewCreature(speciesP[i],world,pt,RandomInteger(0,3));
				SetContents(world,pt,creatureP[i]);
				break;
			}
		}
	}
}

/*
	Function : WantToContinue
	--------------------------------------
	This function is used to ask the user if he wants
	to continue or to stop the game when the user
	click mouse on the map.
*/

bool WantToContinue(creatureADT *creatureP,int num,double *time)
{
	int i;
	int *k;
	string str;
	symtabADT symtab=NewSymbolTable();

	
	for (i=0;i<=num-1;i++)
	{
		if ( Lookup ( symtab  ,SpeciesName ( GetSpecies (creatureP[i]) ) )==UNDEFINED )
		{
			k=GetBlock(sizeof (int) );
			*k=1;
			Enter( symtab , SpeciesName ( GetSpecies (creatureP[i]) ) , k);
		}
		else 
		{
			k=(int*)Lookup(symtab,SpeciesName ( GetSpecies (creatureP[i]) ));
			*k=*k+1;
		}
	}
	printf("\nInventory:\n");
	MapSymbolTable(PrintInventory,symtab,NULL);
	FreeSymbolTable(symtab);

	ChangeTimeInterval(time);
	
	while(TRUE)
	{
		printf("\npress s+Enter to stop and c+Enter to continue :");
		str=GetLine();
		if (StringEqual(str,"s"))  {return FALSE;}
		if (StringEqual(str,"c")) 
		{
			printf("\nTo pause,click mouse on the graph.\n");
			return TRUE;
		}
	}
}

/*
	Function : PrintInventory
	----------------------------------
	This function is used to print how many creature for
	each kind of species when the user click mouse on the
	map.
*/

void PrintInventory(string key,void *value,void *clientData)
{
	printf("    %s: %d\n",key,*(int *)value);
}

/*
	Function : WantToPlayAgain
	------------------------------------
	This function is used to ask the user if he wants
	to play the game of darwin again.
*/

bool WantToPlayAgain()
{
	string str;

	while (TRUE)
	{
		printf("\nWant to play again? (y/n): ");
		str=GetLine();
		if ( StringEqual(str,"y") || StringEqual(str,"yes") )
		{
			return TRUE;
		}
		if ( StringEqual(str,"n") || StringEqual(str,"no") )
		{
			return FALSE;
		}
	}
}
			
/*
	Function : ChangeTimeInterval
	-------------------------------------
	This function is an extention function of mine.
	Because the demo game of darwin acts too fast that
	we cannot see what is happening clearly. So I try to
	make it possible to change the time interval so that 
	it can move slowly. Every time you click mouse on
	the map, you get a chance to chage the time interval.
	It is very easy.
*/

void ChangeTimeInterval(double *time)
{
	string str;
	while(TRUE)
	{
		printf("\nWant to change time interval? ");
		str=GetLine();
		if ( StringEqual(str,"y") || StringEqual(str,"yes") )
		{
			printf("\nTime Interval= ");
			*time=GetReal();
			break;
		}
		if ( StringEqual(str,"n") || StringEqual(str,"no") )
		{
			break;
		}
	}
}













	
