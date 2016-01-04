/*
 * File: geometry.c
 * ----------------
 * This file implements the geometry abstraction.
 */

#include <stdio.h>
#include "genlib.h"
#include "geometry.h"

/*
 * Exported entries
 * ----------------
 * The behavior of these functions is described in the geometry
 * interface, and the implementations seem simple enough that no
 * additional commentary is necessary.
 */

pointT CreatePoint(int x, int y)
{
    pointT pt;

    pt.x = x;
    pt.y = y;
    return (pt);
}

pointT AdjacentPoint(pointT pt, directionT dir)
{
    switch (dir) {
      case North: return (CreatePoint(pt.x, pt.y + 1));
      case East:  return (CreatePoint(pt.x + 1, pt.y));
      case South: return (CreatePoint(pt.x, pt.y - 1));
      case West:  return (CreatePoint(pt.x - 1, pt.y));
    }
}

directionT LeftFrom(directionT dir)
{
    switch (dir) {
      case North: return (West);
      case East:  return (North);
      case South: return (East);
      case West:  return (South);
    }
}

directionT RightFrom(directionT dir)
{
    switch (dir) {
      case North: return (East);
      case East:  return (South);
      case South: return (West);
      case West:  return (North);
    }
}
