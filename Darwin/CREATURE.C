/*
 * File: creature.h
 * ----------------
 * This interface defines the creature abstraction.
 */


#include "genlib.h"
#include "geometry.h"
#include "species.h"
#include "world.h"
#include "worldmap.h"
#include "creature.h"
#include "random.h"
#include "strlib.h"



struct creatureCDT
{
	speciesADT species;
	worldADT world;
	pointT pt;
	directionT dir;
	int step;
};

/*
 * Type: creatureADT
 * -----------------
 * This type is the abstract data type for a creature.
 */
bool IsDetermined ( opcodeT op );
bool IsSatisfied ( opcodeT op, creatureADT creature );
void run ( opcodeT op , creatureADT creature );




/*
 * Function: NewCreature
 * Usage: creature = NewCreature(species, world, pt, dir);
 * -------------------------------------------------------
 * This function creates a new creature of the indicated species
 * that lives in the specified world.  The creature is initially
 * positioned at position pt facing direction dir. The new creature
 * is also inserted into the world using SetContents and is displayed
 * in the world by updating the worldmap.
 */

creatureADT NewCreature(speciesADT species, worldADT world,
                        pointT pt, directionT dir)
{
	creatureADT creature;

	creature = New(creatureADT);
	creature->species = species;
	creature->pt = pt;
	creature->dir = dir;
	creature->step = 1;
	creature->world = world;

	SetContents( world, pt, creature );

	DisplaySquare(pt,SpeciesName(species)[0],dir);

	return creature;
}

/*
 * Function: FreeCreature
 * Usage: FreeCreature();
 * ----------------------
 * This function frees the storage associated with a creature.  It does
 * not free the world in which the creature resides nor the species to
 * which the creature belongs.
 */

void FreeCreature(creatureADT creature)
{
	DisplaySquare(creature->pt,' ',1);
	FreeBlock (creature) ;
}


/*
 * Function: GetSpecies
 * Usage: species = GetSpecies(creature);
 * --------------------------------------
 * This function returns the species to which this creature
 * belongs.
 */

speciesADT GetSpecies(creatureADT creature)
{
	return creature->species;
}

/*
 * Function: TakeOneTurn
 * Usage: TakeOneTurn(creature);
 * -----------------------------
 * This function executes one turn for this creature. Any changes
 * to the creature's state must be reflected in the world and in
 * the worldmap.
 */

void TakeOneTurn(creatureADT creature)
{
	instructionT instruction;
	opcodeT op;


	while (TRUE)
	{
		instruction=ProgramStep(creature->species,creature->step);
		op=instruction.op;

		if ( IsDetermined ( op ) )
		{
			run ( op, creature );
			creature ->step = (creature->step) % (ProgramSize(creature->species)) + 1;
			break;
		}
		else 
		{

			if ( IsSatisfied ( op, creature ) )
			{
				creature->step = instruction.address;
			}
			else
			{
				creature ->step = (creature->step) % (ProgramSize(creature->species)) + 1;
			}
		}
	}
}

/*
	Function : IsDetermined
	----------------------------------
	This function returns TRUE if the operation is
	"Hop" or "Left" or "Right" or "Infect" or "Friend".
	These operations can be carried out immediately.
*/

bool IsDetermined ( opcodeT op )
{
	if (op==Hop || op==Left || op==Right || op==Infect || op==Friend)
	{
		return TRUE;
	}
	else { return FALSE; }
}

/*
	Function : IsSatisfied 
	--------------------------
	If the operation involves "If" , we have to decide
	if it is satisfied. This function just do that.
	"Go" is always satisfied.
*/

bool IsSatisfied ( opcodeT op, creatureADT creature )
{
	bool a;
	creatureADT b;
	pointT pt;

	pt = AdjacentPoint(creature->pt,creature->dir);
	a = InRange ( creature->world ,  pt );
	
	if ( op==IfEmpty )
	{
		if( a )
		{
			b=GetContents ( creature->world, pt );
			return ( b==NULL);
		}	else
		{
			return FALSE;
		};
	}
	if ( op==IfWall ) return !a;
	if ( op==IfSame ) 
	{
		if (!a)
		{
			return FALSE;
		}
		else 
		{
			b=GetContents ( creature->world, pt );
			return  !( b == NULL ) &&
				StringEqual(SpeciesName(creature->species),SpeciesName(b->species));
		}
	}

	if ( op==IfEnemy ) 
	{
		if (!a)
		{
			return FALSE;
		}
		else 
		{
			b=GetContents ( creature->world, pt );
			return  !( b == NULL ) &&
				!StringEqual(SpeciesName(creature->species),SpeciesName(b->species));
		}
	}
	if ( op==IfRandom ) return RandomChance(0.5);
	if ( op==Go ) return TRUE;
}

/*
	Function : run
	-----------------------------
	This function actually carries out what the operation
	should do.
*/

void run ( opcodeT op , creatureADT creature )
{
	pointT pt,pt1;
	int x=AdjacentPoint(creature->pt,creature->dir).x;
	int y=AdjacentPoint(creature->pt,creature->dir).y;
	creatureADT enemy,FRIEND;

	pt=creature->pt;
	pt1=CreatePoint(x,y);

	if ( op==Hop )
	{
		while ( InRange(creature->world,pt1) && GetContents(creature->world,pt1)==NULL )
		{
			creature->pt=pt1;
			pt1=AdjacentPoint(pt1,creature->dir);
		}
		SetContents(creature->world,pt,NULL);
		SetContents(creature->world,creature->pt,creature);
		DisplaySquare(pt,' ',1);
	}

	if ( op==Left )
	{
		creature->dir = LeftFrom(creature->dir);
	}

	if ( op==Right )
	{
		creature->dir = RightFrom(creature->dir);
	}

	if ( op==Infect )
	{
		enemy=GetContents(creature->world,pt1);
		enemy->species=creature->species;
		enemy->step=ProgramStep(creature->species,creature->step).address;
		DisplaySquare(pt1,SpeciesName(enemy->species)[0],enemy->dir);
	}

	if ( op==Friend )
	{
		FRIEND=GetContents(creature->world,pt1);
		FRIEND->step=ProgramStep(creature->species,creature->step).address;
	}
	DisplaySquare(creature->pt,SpeciesName(creature->species)[0],creature->dir);
}




