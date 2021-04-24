#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;


class Tile {
public:
   Shape shape;
   Colour colour;
   Tile(Shape shape, Colour colour);
   void printTile();
   std::string toString();
};

#endif // ASSIGN2_TILE_H
