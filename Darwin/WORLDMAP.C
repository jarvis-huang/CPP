/*
 * File: worldmap.c
 * ----------------
 * This file supports the graphics necessary for Darwin's world.
 */

#include <stdio.h>
#include "genlib.h"
#include "extgraph.h"
#include "geometry.h"
#include "worldmap.h"

/*
 * Constants
 * ---------
 * Pixels          Conversion factor from pixels (dots) to inches
 * LeftMargin      Margin at left edge of window
 * BottomMargin    Margin at bottom edge of window
 * SquareSize      Size of each square in the grid
 * CreatureSize    Size of the bounding box for the creature
 */

#define Pixels        (1 / 72.0)
#define LeftMargin    (1 * Pixels)
#define BottomMargin  (1 * Pixels)
#define SquareSize    (19 * Pixels)
#define CreatureSize  (14 * Pixels)

/* Private function prototypes */

static void EraseSquare(double x, double y);
static void DrawCreatureOutline(double x, double y, directionT dir);
static void DrawCreatureLabel(double x, double y, char keychar,
                              directionT dir);
static void AdjustRotated(double dx, double dy, int theta);
static void DrawRotated(double dx, double dy, int theta);
static void AdjustPen(double dx, double dy);
static void DrawBox(double x, double y, double width, double height);
static void DrawSolidBox(double x, double y, double width, double height);

/* Public entries */

/*
 * Function: InitWorldMap
 * ----------------------
 * This function simply draws the empty grid.  This coding is
 * more efficient than the DrawGrid function.
 */

void InitWorldMap(int columns, int rows)
{
    int i;

    for (i = 0; i <= columns; i++) {
        MovePen(LeftMargin + i * SquareSize, BottomMargin);
        DrawLine(0, rows * SquareSize);
    }
    for (i = 0; i <= rows; i++) {
        MovePen(LeftMargin, BottomMargin + i * SquareSize);
        DrawLine(columns * SquareSize, 0);
    }
}

/*
 * Function: DisplaySquare
 * -----------------------
 * This function draws a creature in the square represented by the
 * point p.  The implementation begins by erasing the interior of
 * the square.  If the square is non-empty, the function then
 * draws the creature outline and the appropriate text label.
 */

void DisplaySquare(pointT p, char keychar, directionT dir)
{
    double x, y;

    x = LeftMargin + p.x * SquareSize;
    y = BottomMargin + p.y * SquareSize;
    EraseSquare(x, y);
    if (keychar != ' ') {
        DrawCreatureOutline(x, y, dir);
        DrawCreatureLabel(x, y, keychar, dir);
    }
}

/* Private functions */

/*
 * Function: EraseSquare
 * Usage: EraseSquare(x, y);
 * -------------------------
 * This function erases the square whose lower left coordinates are
 * at the point (x, y).  To do so, it uses the DrawSolidBox function
 * from Assignment #2 with the pen color set to White.  Because the
 * function must erase only the interior of the square, the white box
 * must be inset by one pixel on each side to avoid erasing the grid.
 */

static void EraseSquare(double x, double y)
{
    SetPenColor("White");
    DrawSolidBox(x + 1 * Pixels, y + 1 * Pixels,
                 SquareSize - 2 * Pixels, SquareSize - 2 * Pixels);
    SetPenColor("Black");
}

/*
 * Function: DrawCreatureOutline
 * Usage: DrawCreatureOutline(x, y, dir);
 * --------------------------------------
 * This function draws the outline of a creature in the square whose
 * lower left coordinates are at the point (x, y).  The creature faces
 * in the direction specified by dir.  The creature is drawn in a
 * fixed orientation using lower-level graphics primitives that draw
 * lines rotated through some angle.
 */

static void DrawCreatureOutline(double x, double y, directionT dir)
{
    int theta;
    double halfCreature;

    switch (dir) {
      case East:  theta =   0; break;
      case North: theta =  90; break;
      case West:  theta = 180; break;
      case South: theta = 270; break;
    }
    halfCreature = CreatureSize / 2;
    MovePen(x + SquareSize / 2, y + SquareSize / 2);
    AdjustRotated(-halfCreature, -halfCreature, theta);
    DrawRotated(halfCreature, 0, theta);
    DrawRotated(halfCreature, halfCreature, theta);
    DrawRotated(-halfCreature, halfCreature, theta);
    DrawRotated(-halfCreature, 0, theta);
    DrawRotated(0, -CreatureSize, theta);
}

/*
 * Function: DrawCreatureLabel
 * Usage: DrawCreatureLabel(x, y, keychar, dir);
 * ---------------------------------------------
 * This function draws the character in the center of the outline.
 * The complexity comes from the fact that the starting position
 * needs to be adjusted slightly depending on the direction in
 * order for the letter to appear centered.  To avoid allocating
 * memory, the function converts the character to a string
 * explicitly without calling CharToString.
 */

static void DrawCreatureLabel(double x, double y, char keychar,
                              directionT dir)
{
    int xOffset, yOffset;
    char buffer[2];

    switch (dir) {
      case East:  xOffset = -4; yOffset = -4; break;
      case North: xOffset = -2; yOffset = -5; break;
      case West:  xOffset = -1; yOffset = -4; break;
      case South: xOffset = -2; yOffset = -3; break;
    }
    buffer[0] = keychar;
    buffer[1] = '\0';
    MovePen(x + SquareSize / 2 + xOffset * Pixels,
            y + SquareSize / 2 + yOffset * Pixels);
    DrawTextString(buffer);
    UpdateDisplay();
}

/*
 * Function: AdjustRotated
 * Usage: AdjustRotated(dx, dy, theta);
 * ------------------------------------
 * This function is like AdjustPen except that the actual offsets
 * are rotated by theta degrees.  To avoid the overhead of calling
 * trigonometric functions, this implementation handles only the
 * principal compass point angles (0, 90, 180, and 270).
 */

static void AdjustRotated(double dx, double dy, int theta)
{
    switch (theta) {
        case   0: AdjustPen(dx, dy); break;
        case  90: AdjustPen(-dy, dx); break;
        case 180: AdjustPen(-dx, -dy); break;
        case 270: AdjustPen(dy, -dx); break;
        default:  Error("AdjustRotated: Illegal angle");
    }
}

/*
 * Function: DrawRotated
 * Usage: DrawRotated(dx, dy, theta);
 * ----------------------------------
 * This function is like DrawLine except that the offsets
 * are rotated by theta degrees.
 */

static void DrawRotated(double dx, double dy, int theta)
{
    switch (theta) {
        case   0: DrawLine(dx, dy); break;
        case  90: DrawLine(-dy, dx); break;
        case 180: DrawLine(-dx, -dy); break;
        case 270: DrawLine(dy, -dx); break;
        default:  Error("DrawRotated: Illegal angle");
    }
}

/*
 * Function: AdjustPen
 * Usage: AdjustPen(dx, dy);
 * -------------------------
 * This procedure adjusts the current point by moving it
 * dx inches from its current x coordinate and dy inches
 * from its current y coordinate.  As with MovePen, no
 * line is actually drawn.
 */

static void AdjustPen(double dx, double dy)
{
    MovePen(GetCurrentX() + dx, GetCurrentY() + dy);
}

/*
 * Function: DrawBox
 * Usage: DrawBox(x, y, width, height)
 * -----------------------------------
 * This function draws a rectangle of the given width and
 * height with its lower left corner at (x, y).
 */

static void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

/*
 * Function: DrawSolidBox
 * Usage: DrawSolidBox(x, y, width, height);
 * -----------------------------------------
 * This function draws a box like DrawBox but fills it in with
 * a solid color using the filled region mechanism in the
 * extended graphics library.  This implementation also draws
 * the outline to ensure that the filled box is the same size
 * as the DrawBox output.
 */

static void DrawSolidBox(double x, double y,
                  double width, double height)
{
    StartFilledRegion(1.0);
    DrawBox(x, y, width, height);
    EndFilledRegion();
    DrawBox(x, y, width, height);
}
