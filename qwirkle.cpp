#include "Game.h"
#include "InputCodes.h"
#include "LinkedList.h"

#include <exception>
#include <iostream>
#include <string>

void printMenu();
void printCredits();
void printStudent(std::string name, std::string id);
void printQuitMessage();
void loadGame(std::string fileName);

int main(void)
{
   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;
   bool validInput = false;
   std::string input;
   printMenu();
   while (validInput == false)
   {
      std::getline(std::cin, input);
      if (input == NEW_GAME)
      {
         validInput = true;
         std::cout << std::endl;
         std::cout << "Starting a New Game" << std::endl;
         std::cout << std::endl;

         // Create a game. Game will create the players

         Game* game = new Game();
         std::cout << "Let's Play!" << std::endl;
         game->playGame();
         delete game; // move to the end as we would need the game still (if we
                      // were doing high scores or something)
      }
      if (input == LOAD_GAME)
      {
         validInput = true;
         std::cout << std::endl;
         std::cout << "Enter the filename from which load a game" << std::endl;
         std::cout << "> ";
         // get file and validate
         // if valid
         std::cout << std::endl;
         std::cout << "Qwirkle game successfully loaded" << std::endl;
         // spec doesn't say what to do if invalid.
      }
      if (input == CREDITS)
      {
         validInput = true;
         std::cout << std::endl;
         printCredits();
      }
      if (input == QUIT)
      {
         validInput = true;
         std::cout << std::endl;
         printQuitMessage();
      }
      if (std::cin.eof())
      {
         validInput = true;
         printQuitMessage();
      }
      if (validInput == false)
      {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
      }
      // temp to make it go back to main menu after showing credits.
      if (input == "3")
      {
         validInput = false;
         printMenu();
      }
   }

   return EXIT_SUCCESS;
}

void loadGame(std::string fileName)
{
   std::ifstream savedGame(fileName + ".save");
   if (savedGame)
   {
      // player one name
      std::string playerOneName = "";
      getline(savedGame, playerOneName);
      std::cout << playerOneName << std::endl;

      // player one score
      std::string playerOneScoreStr = "";
      getline(savedGame, playerOneScoreStr);
      int playerOneScore = std::stoi(playerOneScoreStr);
      std::cout << playerOneScore << std::endl;

      // player one hand
      std::string playerOneHand = "";
      getline(savedGame, playerOneHand);
      std::cout << playerOneHand << std::endl;

      // player two name
      std::string playerTwoName = "";
      getline(savedGame, playerTwoName);
      std::cout << playerTwoName << std::endl;

      // player two score
      std::string playerTwoScoreStr = "";
      getline(savedGame, playerTwoScoreStr);
      int playerTwoScore = std::stoi(playerTwoScoreStr);
      std::cout << playerTwoScore << std::endl;

      // player two hand
      std::string playerTwoHand = "";
      getline(savedGame, playerTwoHand);
      std::cout << playerTwoHand << std::endl;

      // board dimensions
      std::string dimStr = "";
      getline(savedGame, dimStr);
      size_t commaIndex = dimStr.find(",");
      int dimY          = std::stoi(dimStr.substr(0, commaIndex));
      int dimX          = std::stoi(dimStr.substr(commaIndex + 1));
      std::cout << "Height:" << dimY << ", Width:" << dimX << std::endl;

      // board state
      std::string boardState = "";
      getline(savedGame, boardState);
      std::cout << boardState << std::endl;

      // tile bag contents
      std::string bagContents = "";
      getline(savedGame, bagContents);
      std::cout << bagContents << std::endl;

      // current player name
      std::string currentPlayerName = "";
      getline(savedGame, currentPlayerName);
      std::cout << currentPlayerName << std::endl;
   }
}

void printMenu()
{
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << std::endl;
   std::cout << "> ";
}

void printCredits()
{
   std::cout << "----------------------------------" << std::endl;
   printStudent("Martin Krisnanto Putra", "3608646");
   printStudent("Riley James Gozzard", "3811315");
   printStudent("Ryan Iem", "3700995");
   printStudent("Thomas Joseph Dib", "3838765");
   std::cout << "----------------------------------" << std::endl;
}

void printStudent(std::string name, std::string id)
{
   std::cout << "Name: " << name << std::endl;
   std::cout << "Student ID: " << id << std::endl;
   std::cout << "Email: s" << id << "@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
}

void printQuitMessage()
{
   std::cout << "Goodbye" << std::endl;
}