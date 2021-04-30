
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
   Tile* grab(int index);
   bool isEmpty();
   std::string getContents();

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
