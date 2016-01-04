
/*
 * File: species.h
 * ---------------
 * This interface defines the species abstraction.
 */


#include "genlib.h"
#include "species.h"
#include "ctype.h"
#include "strlib.h"
#include "simpio.h"


#define MaxProgram 250
 
/*
 * Type: speciesADT
 * ----------------
 * This type is the abstract data type for a species.
 */
struct speciesCDT
{
	instructionT *instruction;
	int num;
	string name;
};


static opcodeT Convert(string operation);


/*
 * Type: instructionT
 * ------------------
 * The type instructionT is used to represent an instruction
 * and consists of a pair of an operation code and an integer.
 */


/*
 * Function: ReadSpecies
 * Usage: species = ReadSpecies(filename);
 * ---------------------------------------
 * This function reads in a new species from the specified filename.
 * To find the file, the function looks in a subfolder named
 * "Creatures".  If there is no file with the indicated name in
 * that subfolder, the function returns NULL.
 */

speciesADT ReadSpecies(string filename)
{
	FILE *infile;
	speciesADT species;
	int num=0;
	int address;
	string temp;
	char line[MaxProgram];

	species=New(speciesADT);
	infile=fopen(Concat("Creatures\\", filename),"r");
	species->name=ReadLine(infile);
	while ( !StringLength ( ReadLine(infile)) == 0 )
	{
		num++;
	}
	fclose(infile);
	
	species->num=num;
	species->instruction=GetBlock((num)*sizeof(instructionT));

	infile=fopen(Concat("Creatures\\", filename),"r");

	num=0;
	ReadLine(infile);

	while (TRUE)
	{
		temp = ReadLine(infile);
		if (StringLength(temp) == 0)  {break;}
		address = 1;
		sscanf( temp, "%s %d", line, &address );

		(species->instruction)[num].address=address;
		(species->instruction)[num].op=Convert(line);
		num++;		
	}
	
	fclose(infile);
	return species;
}

/*
 * Function: FreeSpecies
 * Usage: FreeSpecies(species);
 * ----------------------------
 * This function frees the storage associated with a species.
 */

void FreeSpecies(speciesADT species)
{
	FreeBlock(species->instruction);
	FreeBlock(species);
}

/*
 * Function: SpeciesName
 * Usage: name = SpeciesName(species);
 * -----------------------------------
 * This function returns the name for an existing species.
 */

string SpeciesName(speciesADT species)
{
	return species->name;
}


/*
 * Function: ProgramSize
 * Usage: nSteps = ProgramSize(species);
 * -------------------------------------
 * This function returns the number of instructions in the program
 * for this species.
 */

int ProgramSize(speciesADT species)
{
	return species->num;
}

/*
 * Function: ProgramStep
 * Usage: statement = ProgramStep(species, k);
 * -------------------------------------------
 * This function returns the kth instruction in the program for
 * this species, where program steps are numbered beginning at 1.
 * Attempting to select an instruction outside the program range
 * generates an error.
 */

instructionT ProgramStep(speciesADT species, int k)
{
	if(k > ProgramSize( species ))
		Error(" Out of range\n");
	return species->instruction[k - 1];
}

/*
	Function : Convert
	----------------------------
	This function converts a string to its corresponding
	operation.
*/

static opcodeT Convert(string operation)
{
	operation=ConvertToLowerCase(operation);

	if(StringEqual(operation, "hop")) return(Hop);
	if(StringEqual(operation, "left")) return(Left);
	if(StringEqual(operation, "right")) return(Right);
	if(StringEqual(operation, "infect")) return(Infect);
	if(StringEqual(operation, "friend")) return(Friend);
	if(StringEqual(operation, "ifempty")) return(IfEmpty);
	if(StringEqual(operation, "ifwall")) return(IfWall);
	if(StringEqual(operation, "ifsame")) return(IfSame);
	if(StringEqual(operation, "ifenemy")) return(IfEnemy);
	if(StringEqual(operation, "ifrandom")) return(IfRandom);
	if(StringEqual(operation, "go")) return(Go);
}

