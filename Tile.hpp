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
   // return a string for the given tile (e.g. B6)
   std::string toString();
   // print a tile in white (e.g. B6)
   void printTile();

   // INDIVIDUAL

   // return a string for the given tile (e.g B6)
   std::string toStringColour();
   // print a tile (e.g. B6) in colour instead of white
   void printTileColour();

private:
   Shape shape;
   Colour colour;
};

#endif // ASSIGN2_TILE_H
