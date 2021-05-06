#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.hpp"

class Node
{
public:
   Node(Tile* tile, Node* next);

   Tile* tile;
   Node* next;
};

#endif // ASSIGN2_NODE_H
