#include "LinkedList.hpp"

LinkedList::LinkedList()
    : head(nullptr)
    , tail(nullptr)
{
   // no further initialization needed
}

LinkedList::~LinkedList()
{
   Node* current = head;
   while (current != nullptr)
   {
      Node* next = current->next;
      delete current;
      current = next;
   }
   current = nullptr;
   head    = nullptr;
   tail    = nullptr;
}

void LinkedList::push(Tile* tile)
{
   Node* node = new Node(tile, nullptr);
   if (tail == nullptr)
   {
      head = node;
      tail = node;
   }
   else
   {
      tail->next = node;
      tail       = node;
   }
}

Tile* LinkedList::pop()
{
   Tile* tempTile = nullptr;
   Node* tempNode = nullptr;

   if (head != nullptr)
   {
      tempNode = head;
      if (tail == head)
      {
         tail = nullptr;
      }
      head = head->next;
   }

   if (tempNode != nullptr)
   {
      tempTile = tempNode->tile;
      delete tempNode;
      tempNode = nullptr;
   }

   return tempTile;
}

Tile* LinkedList::grab(int index)
{
   Tile* tempTile = nullptr;

   Node* currentNode = head;
   Node* prevNode    = nullptr;
   int currentIndex  = 0;
   bool found        = false;
   while (currentNode != nullptr && !found)
   {
      if (currentIndex == index)
      {
         found = true;
      }
      else
      {
         currentIndex++;
         prevNode    = currentNode;
         currentNode = currentNode->next;
      }
   }

   // when found
   if (found)
   {
      // remove Node from chain of linked list
      if (prevNode != nullptr)
      {
         prevNode->next = currentNode->next;
      }

      // make sure head and tail are valid
      if (head == tail)
      {
         head = nullptr;
         tail = nullptr;
      }
      else if (head == currentNode && head != nullptr)
      {
         head = head->next;
      }
      else if (tail == currentNode && tail != nullptr)
      {
         tail = prevNode;
      }

      // grab Tile and cleanup Node
      if (currentNode != nullptr)
      {
         tempTile = currentNode->tile;
         delete currentNode;
         currentNode = nullptr;
      }
   }

   return tempTile;
}

bool LinkedList::isEmpty()
{
   return head == nullptr;
}

std::string LinkedList::getContents(bool colourPrinting)
{
   std::string contents = "";

   Node* currentNode = head;
   while (currentNode != nullptr)
   {
      if (currentNode != head)
      {
         contents += ',';
      }

      if (colourPrinting)
      {
         contents += currentNode->tile->toStringColour();
      }
      else
      {
         contents += currentNode->tile->toString();
      }
      currentNode = currentNode->next;
   }

   return contents;
}

int LinkedList::findTileIndex(std::string tileString)
{
   int tileIndex = -1;

   int currentIndex  = 0;
   Node* currentNode = head;
   bool found        = false;
   while (currentNode != nullptr && !found)
   {
      if (currentNode->tile->toString() == tileString)
      {
         found = true;
      }
      else
      {
         currentNode = currentNode->next;
         currentIndex++;
      }
   }

   if (found)
   {
      tileIndex = currentIndex;
   }

   return tileIndex;
}

int LinkedList::getSize()
{
   int nodeCount  = 0;
   Node* tempNode = nullptr;

   if (head != nullptr)
   {
      tempNode = head;
      nodeCount++;
      while (tempNode->next != nullptr)
      {
         tempNode = tempNode->next;
         nodeCount++;
      }
   }

   return nodeCount;
}

Tile* LinkedList::getTileAtIndex(int tileIndex)
{
   Tile* tempTile  = nullptr;
   Node* tempNode  = nullptr;
   int nodeCounter = 0;

   if (head != nullptr)
   {
      tempNode = head;
      while (tempNode != nullptr)
      {
         if (nodeCounter == tileIndex)
         {
            tempTile = tempNode->tile;
         }
         tempNode = tempNode->next;
         nodeCounter++;
      }
   }

   return tempTile;
}