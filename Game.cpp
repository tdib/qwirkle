#include "Game.h"

// Playing a fresh new game
Game::Game() {
   // TODO

   // initialiseTiles(); // ?
    
}

// Loading a saved game
Game::Game(std::string* gameInfo) {
   // TODO

}

Game::~Game(){
   // TODO
}

void Game::playGame() {

   bool validInput = false;
   std::string input;

   while (!std::cin.eof() && validInput == false) {
      
      try {
         std::cout << "> ";
         std::cin >> input;

         // Need to check the input. For now, hard-coded with random inputs
         if (input == "place") {
            // TODO
            validInput = true;
         } else if (input == "quit") {
            // TODO: quit the game, THEN quit the qwirkle program?
            validInput = true;
         } else {
            throw std::invalid_argument("Invalid Input");
         }
         
      } catch (std::exception& e) {
         std::cout << e.what() << std::endl;
      }
   }

}

void Game::initialiseTiles() {
   // TODO

   // should initialise the board too

   try {

      std::ifstream file("tiles.txt");
      file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

      Colour readColour; // char
      Shape readShape; // int

      while (!file.eof()) {
         file >> readColour;
         file >> readShape;
         std::cout << readColour << readShape << std::endl;

         // Note: shuffle INSIDE of vector
         // TODO: put tiles into the LinkedList Bag after it's implemented?

      }

      file.close();

   } catch (std::exception& e) {
      std::cout << "Error reading tiles.txt" << std::endl;
      throw e;
   }

}

void Game::loadTiles(std::string* string) {
   // TODO
}

void Game::printState() {
   // TODO

   std::cout << std::endl;
   std::cout << " ";

   for (int i = 0; i < 26; i++) { // Columns
      std::cout << "  " << i;
   }

   std::cout << std::endl;
   std::cout << "  ";

   for (int j = 0; j < 47; j++) {
      std::cout << "--";
   }

   std::cout << std::endl;

   for (char k = 'A'; k <= 'Z'; k++) { // Rows
      std::cout << k << " |" << std::endl;
   }

}

bool Game::saveGame() {
   // TODO
   // bool false if the file is open or something?
   return false;

}

void Game::quit() {
   // TODO
   // crash :)
}