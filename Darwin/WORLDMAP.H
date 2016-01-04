/*
 * File: worldmap.h
 * ----------------
 * This interface supports the graphics for the Darwin world.
 */

#ifndef _worldmap_h
#define _worldmap_h

#include "genlib.h"
#include "geometry.h"

/*
 * Function: InitWorldMap
 * Usage: InitWorldMap(columns, rows);
 * -------------------------------------
 * This function opens and displays two windows on the screen, one
 * for the Darwin world and one for the console.  This call must be
 * made before any other calls are made using this package and before
 * any output to the standard I/O channels.  The parameters
 * columns and rows specify the size of the world, although
 * some squares will be outside of the visible display if the
 * world is made too large.
 */

void InitWorldMap(int columns, int rows);

/*
 * Function: DisplaySquare
 * Usage: DisplaySquare(sq, keychar, dir);
 * ---------------------------------------
 * This function changes the display for the indicated square
 * (the location of which is expressed as a point) so that
 * it contains the "creature" indicated by the character keychar
 * facing in the direction specified by dir.  If keychar is a
 * space, the square is displayed as empty and the direction is
 * ignored.
 */

void DisplaySquare(pointT sq, char keychar, directionT dir);

#endif
