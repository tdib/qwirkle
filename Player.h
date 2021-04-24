#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "Tile.h"
#include "Board.h"
#include "Bag.h"

class Player
{
   public:
      Player();
      Player(std::string playerInfo);
      ~Player();
      bool drawTile();
      bool placeTile(Tile* tile, std::string coordinate);
      bool swapTile(Tile* tileToSwap);
      void addScore();

      std::string getName();
      void setName(std::string newName);
      int getScore();
      std::string getHand();

      void setBag(Bag* bag);
      void setBoard(Board* board);
   
   private:
      Bag* bag;
      Board* board;
      LinkedList* hand;
      std::string name;
      int score;  
};

#endif // PLAYER_H