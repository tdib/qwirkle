#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "InputCodes.h"

class Game {
public:

   Game();
   Game(std::string* fileName);
   ~Game();

   // Public or else qwirkle.cpp can't use them
   void playGame();
   void initalisePlayers();
   void loadTiles(std::string* tilesInfo);
   void printState();
   bool saveGame();
   void quit();
   std::vector<std::string> splitString(std::string rawUserInput, char delimiter);

private:

   // player as a vector
   
   Board* board;
   Bag* bag;
   std::vector<Player*> players;

};

#endif // ASSIGN2_GAME_H
