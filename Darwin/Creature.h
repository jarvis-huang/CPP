/*
 * File: creature.h
 * ----------------
 * This interface defines the creature abstraction.
 */

#ifndef _creature_h
#define _creature_h

#include "genlib.h"
#include "geometry.h"
#include "species.h"
#include "world.h"
#include "strlib.h"


/*
 * Type: creatureADT
 * -----------------
 * This type is the abstract data type for a creature.
 */

typedef struct creatureCDT *creatureADT;

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
                        pointT pt, directionT dir);


/*
 * Function: FreeCreature
 * Usage: FreeCreature();
 * ----------------------
 * This function frees the storage associated with a creature.  It does
 * not free the world in which the creature resides nor the species to
 * which the creature belongs.
 */

void FreeCreature(creatureADT creature);

/*
 * Function: GetSpecies
 * Usage: species = GetSpecies(creature);
 * --------------------------------------
 * This function returns the species to which this creature
 * belongs.
 */

speciesADT GetSpecies(creatureADT creature);

/*
 * Function: TakeOneTurn
 * Usage: TakeOneTurn(creature);
 * -----------------------------
 * This function executes one turn for this creature. Any changes
 * to the creature's state must be reflected in the world and in
 * the worldmap.
 */

void TakeOneTurn(creatureADT creature);

bool IsDetermined ( opcodeT op );

bool IsSatisfied ( opcodeT op, creatureADT creature );

void run ( opcodeT op , creatureADT creature );




#endif
