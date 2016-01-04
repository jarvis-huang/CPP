/*
 * File: geometry.h
 * ----------------
 * This interface provides some extremely simple types
 * and operations that are useful for manipulating points
 * on an x-y grid.
 */

#ifndef _geometry_h
#define _geometry_h

#include "genlib.h"

/*
 * Type: pointT
 * ------------
 * The type pointT is used to encapsulate a coordinate pair
 * into a single value.  Because the record representation
 * makes good intuitive sense and adding an extra level of
 * pointers to the reference would reduce both execution and
 * storage efficiency, this type is exported in its concrete
 * form.
 */

typedef struct {
    int x, y;
} pointT;

/*
 * Type: directionT
 * ----------------
 * This type is an example of an "enumerated type" in C.  The
 * values of type directionT are simply the constants listed in
 * the braces following the enum keyword.  Thus, a variable of
 * type directionT can take on one of the four values North, East,
 * South, and West.
 */

typedef enum { North, East, South, West } directionT;

/*
 * Function: CreatePoint
 * Usage: pt = CreatePoint(x, y);
 * ------------------------------
 * This function combines the x and y coordinates into a pointT
 * structure and returns that value.
 */

pointT CreatePoint(int x, int y);

/*
 * Function: AdjacentPoint
 * Usage: newpt = AdjacentPoint(pt, dir);
 * --------------------------------------
 * This function returns the pointT that results from moving one
 * square in the indicated direction from pt.
 */

pointT AdjacentPoint(pointT pt, directionT dir);

/*
 * Functions: LeftFrom, RightFrom
 * Usage: newdir = LeftFrom(dir);
 *        newdir = RightFrom(dir);
 * -------------------------------
 * These functions return the directions that result from turning
 * left or right from the given starting direction.
 */

directionT LeftFrom(directionT dir);
directionT RightFrom(directionT dir);

#endif
