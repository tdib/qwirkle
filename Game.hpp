#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Bag.hpp"
#include "InputCodes.hpp"
#include "Player.hpp"
#include "Tile.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Game
{
public:
   Game(int numPlayers);
   Game(std::string* fileName);
   ~Game();

   // Public or else qwirkle.cpp can't use them
   void playGame();
   void initalisePlayers();
   void loadTiles(std::string* tilesInfo);
   void printState();
   bool saveGame(std::string saveFileName);
   void quit();
   std::vector<std::string> splitString(
      std::string rawUserInput, char delimiter);
   bool isValidName(std::string name);

private:
   // player as a vector

   Board* board;
   Bag* bag;
   std::vector<Player*> players;
   int numPlayers;
};

#endif // ASSIGN2_GAME_H
