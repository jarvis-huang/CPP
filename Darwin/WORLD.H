/*
 * File: world.h
 * -------------
 * This interface defines an abstraction which can be used
 * to store objects in an x/y cartesian world.  This abstraction
 * is completely independent of the graphical display, and the
 * client is responsible for any screen updates that are required.
 */

#ifndef _world_h
#define _world_h

#include "genlib.h"
#include "stdio.h"
#include "simpio.h"
#include "worldmap.h"
#include "geometry.h"

/*
 * Type: worldADT
 * --------------
 * This abstract type stores the data for a "world," which is
 * defined to be a two-dimensional grid capable of storing
 * arbitrary objects represented as pointers whose type is
 * understood only by the client.
 */

typedef struct worldCDT *worldADT;

/*
 * Function: NewWorld
 * Usage: world = NewWorld(width, height);
 * ---------------------------------------
 * This function creates a new world consisting of width columns
 * and height rows, each of which is numbered beginning at 0.
 * A newly created world contains no objects, and each element of
 * the world will be initialized to NULL.
 */

worldADT NewWorld(int width, int height);

/*
 * Function: FreeWorld
 * Usage: FreeWorld(world);
 * ------------------------
 * This function frees all of the storage associated with a world.
 * It does not free the objects that have been placed in the world,
 * since those pointers are understood only by the client.
 */

void FreeWorld(worldADT world);


/*
 * Functions: WorldWidth, WorldHeight
 * Usage: width = WorldWidth(world);
 *        height = WorldHeight(world);
 * -----------------------------------
 * These functions return the width and the height of a world,
 * respectively.
 */

int WorldWidth(worldADT world);
int WorldHeight(worldADT world);

/*
 * Function: InRange
 * Usage: if (InRange(world, pt)) . . .
 * ------------------------------------
 * This function returns TRUE if the specified point pt is within
 * the boundaries  of the world.
 */

bool InRange(worldADT world, pointT pt);

/*
 * Function: SetContents
 * Usage: SetContents(world, pt, obj);
 * -----------------------------------
 * This function places the object obj into the world at the
 * position indicated by pt. If pt is out of range, an error is generated.
 */

void SetContents(worldADT world, pointT pt, void *obj);

/*
 * Function: GetContents
 * Usage: obj = GetContents(world, pt);
 * ------------------------------------
 * This function returns the object currently in the world at
 * position pt. If pt is out of range, an error is generated.
 */

void *GetContents(worldADT world, pointT pt);

#endif
