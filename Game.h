#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include "Tile.h"

class Game {
public:

   Game();
   Game(std::string* string);
   ~Game();

   // Public or else qwirkle.cpp can't use them
   void initialiseTiles();
   void loadTiles(std::string* string);
   void printState();
   bool saveGame();
   void quit();

private:

};

#endif // ASSIGN2_GAME_H
