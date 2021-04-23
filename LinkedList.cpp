
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), tail(nullptr)
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
   head = nullptr;
   tail = nullptr;
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
      tail = node;
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
   Node* prevNode = nullptr;
   int currentIndex = 0;
   bool found = false;
   while (currentNode != nullptr && !found)
   {
      if (currentIndex == index)
      {
         found = true;
      }
      else
      {
         currentIndex++;
         prevNode = currentNode;
         currentNode = currentNode->next;
      }
   }

   // when found
   if (found) {
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
         tail = nullptr;
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

std::string LinkedList::getContents()
{
   std::string contents = "";

   // TODO: use a function instead of treating Tile as public
   Node* currentNode = head;
   while (currentNode != nullptr)
   {
      if (currentNode != head)
      {
         contents += ',';
      }
      contents += currentNode->tile->colour;
      contents += std::to_string(currentNode->tile->shape);
      currentNode = currentNode->next;
   }

   return contents;
}
