#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.hpp"

#include <iostream>
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
   Tile(Shape shape, Colour colour);
   std::string toString();
   void printTile();

   // INDIVIDUAL - used for printing in colour instead of white
   std::string toStringColour();
   void printTileColour();

private:
   Shape shape;
   Colour colour;
};

#endif // ASSIGN2_TILE_H
