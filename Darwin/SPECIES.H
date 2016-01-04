/*
 * File: species.h
 * ---------------
 * This interface defines the species abstraction.
 */

#ifndef _species_h
#define _species_h

#include "genlib.h"

/*
 * Type: speciesADT
 * ----------------
 * This type is the abstract data type for a species.
 */

typedef struct speciesCDT *speciesADT;

/*
 * Type: opcodeT
 * -------------
 * The type opcodeT is an enumeration of all of the legal
 * command names.
 */

typedef enum {
    Hop, Left, Right, Infect, Friend,
    IfEmpty, IfWall, IfSame, IfEnemy, IfRandom,
    Go
} opcodeT;

/*
 * Type: instructionT
 * ------------------
 * The type instructionT is used to represent an instruction
 * and consists of a pair of an operation code and an integer.
 */

typedef struct {
    opcodeT op;
    int address;
} instructionT;

/*
 * Function: ReadSpecies
 * Usage: species = ReadSpecies(filename);
 * ---------------------------------------
 * This function reads in a new species from the specified filename.
 * To find the file, the function looks in a subfolder named
 * "Creatures".  If there is no file with the indicated name in
 * that subfolder, the function returns NULL.
 */

speciesADT ReadSpecies(string filename);

/*
 * Function: FreeSpecies
 * Usage: FreeSpecies(species);
 * ----------------------------
 * This function frees the storage associated with a species.
 */

void FreeSpecies(speciesADT species);

/*
 * Function: SpeciesName
 * Usage: name = SpeciesName(species);
 * -----------------------------------
 * This function returns the name for an existing species.
 */

string SpeciesName(speciesADT species);

/*
 * Function: ProgramSize
 * Usage: nSteps = ProgramSize(species);
 * -------------------------------------
 * This function returns the number of instructions in the program
 * for this species.
 */

int ProgramSize(speciesADT species);

/*
 * Function: ProgramStep
 * Usage: statement = ProgramStep(species, k);
 * -------------------------------------------
 * This function returns the kth instruction in the program for
 * this species, where program steps are numbered beginning at 1.
 * Attempting to select an instruction outside the program range
 * generates an error.
 */

instructionT ProgramStep(speciesADT species, int k);

#endif
