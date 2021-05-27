
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.hpp"

#include <string>

class LinkedList
{
public:
   LinkedList();
   ~LinkedList();
   // add a tile to the back of the linkedlist
   void push(Tile* tile);
   // remove a tile from the front of the linkedlist
   Tile* pop();
   // grabs (removes) a tile from a specific index in the LinkedList
   Tile* grab(int index);
   // checks if there are no elements in the list
   bool isEmpty();
   // returns string of tiles in bag (in colour or white)
   std::string getContents(bool colourPrinting);
   // returns the index of the first matching tile in the LinkedList (if any).
   // returns -1 otherwise
   int findTileIndex(std::string tileString);

   // INDIVIDUAL

   // returns the number of tiles in the linkedlist
   int getSize();
   // returns a tile at a specific index, but does not remove it -
   // used to scan a player's tiles
   Tile* getTileAtIndex(int tileIndex);

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
