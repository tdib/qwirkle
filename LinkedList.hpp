
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.hpp"

#include <string>

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();
   void push(Tile* tile);
   Tile* pop();
   // Grabs a tile from a specific index in the LinkedList
   Tile* grab(int index);
   bool isEmpty();
   std::string getContents();
   // Returns the index of the first matching tile in the LinkedList (if any).
   // Returns -1 otherwise
   int findTileIndex(std::string tileString);

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
