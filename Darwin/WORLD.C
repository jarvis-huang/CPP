/*
 * File: world.h
 * -------------
 * This interface defines an abstraction which can be used
 * to store objects in an x/y cartesian world.  This abstraction
 * is completely independent of the graphical display, and the
 * client is responsible for any screen updates that are required.
 */


#include "genlib.h"
#include "simpio.h"
#include "stdio.h"
#include "creature.h"
#include "geometry.h"
#include "world.h"


 struct worldCDT
 {
	 creatureADT **grid;
	 int width;
	 int height;
 };

 /*
 * Type: worldADT
 * --------------
 * This abstract type stores the data for a "world," which is
 * defined to be a two-dimensional grid capable of storing
 * arbitrary objects represented as pointers whose type is
 * understood only by the client.
 */


/*
 * Function: NewWorld
 * Usage: world = NewWorld(width, height);
 * ---------------------------------------
 * This function creates a new world consisting of width columns
 * and height rows, each of which is numbered beginning at 0.
 * A newly created world contains no objects, and each element of
 * the world will be initialized to NULL.
 */

worldADT NewWorld(int width, int height)
{
	creatureADT **grid;
	int i,k;
	worldADT world;

	world=New(worldADT);
	grid=GetBlock( height * sizeof ( creatureADT* ) );
	for ( i=0; i<=height; i++ )
	{
		grid[i] = GetBlock ( width * sizeof (creatureADT) );
		for ( k=0 ; k<=width-1 ; k++ )
		{
			grid[i][k]=NULL;
		}
	}

	world->grid=grid;
	world->width=width;
	world->height=height;

	return world;
}

/*
 * Function: FreeWorld
 * Usage: FreeWorld(world);
 * ------------------------
 * This function frees all of the storage associated with a world.
 * It does not free the objects that have been placed in the world,
 * since those pointers are understood only by the client.
 */

void FreeWorld(worldADT world)
{
	int i;

	for ( i=0 ; i< world->height ; i++ )
	{
		FreeBlock ( (world->grid)[i] );
	};

//	free ( (world->grid) );
	FreeBlock (world);
}


/*
 * Functions: WorldWidth, WorldHeight
 * Usage: width = WorldWidth(world);
 *        height = WorldHeight(world);
 * -----------------------------------
 * These functions return the width and the height of a world,
 * respectively.
 */

int WorldWidth(worldADT world)
{
	return world->width;
}

int WorldHeight(worldADT world)
{
	return world->height;
}


/*
 * Function: InRange
 * Usage: if (InRange(world, pt)) . . .
 * ------------------------------------
 * This function returns TRUE if the specified point pt is within
 * the boundaries  of the world.
 */

bool InRange(worldADT world, pointT pt)
{
	if ( 0<=pt.x && pt.x<=world->width-1 && 0<=pt.y && pt.y<=world->height-1 )
	{
		return TRUE;
	}
	else { return FALSE; }
}

/*
 * Function: SetContents
 * Usage: SetContents(world, pt, obj);
 * -----------------------------------
 * This function places the object obj into the world at the
 * position indicated by pt. If pt is out of range, an error is generated.
 */

void SetContents(worldADT world, pointT pt, void *obj)
{
	if (InRange(world,pt)) 
	{
		(world->grid)[pt.x][pt.y] = obj;
	}
	else 
	{
		Error ("Cannot reference");
	}
}

/*
 * Function: GetContents
 * Usage: obj = GetContents(world, pt);
 * ------------------------------------
 * This function returns the object currently in the world at
 * position pt. If pt is out of range, an error is generated.
 */

void *GetContents(worldADT world, pointT pt)
{
	if (InRange(world,pt)) 
	{
		return (world->grid)[pt.x][pt.y];
	}
	else 
	{
		Error ("Cannot reference");
	}
}



