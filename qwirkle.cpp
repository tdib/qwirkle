#include "Game.hpp"
#include "InputCodes.hpp"
#include "LinkedList.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

void printMenu();
void printCredits();
void printStudent(std::string name, std::string id);
void printQuitMessage();
// bool loadGame(Game* game, std::string fileName);
bool loadGame(std::string fileName);

int main(void)
{
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;
   bool loopAgain = true;
   std::string input;
   printMenu();
   while (loopAgain == true)
   {
      std::cout << "> ";
      try
      {
         std::getline(std::cin, input);
         if (input == NEW_GAME)
         {
            loopAgain = false;
            std::cout << std::endl;
            std::cout << "Starting a New Game" << std::endl;
            std::cout << std::endl;

            // Create a game. Game will create the players
            Game* game = new Game(2);
            game->playGame();
            if (std::cin.eof())
            {
               printQuitMessage();
            }
            delete game; // move to the end as we would need the game still
                         // (if we were doing high scores or something)
         }
         else if (input == LOAD_GAME)
         {
            loopAgain            = false;
            std::string fileName = "";
            std::cout << std::endl;
            std::cout << "Enter the filename from which to load a game"
                      << std::endl;

            bool loopFileNameAgain = true;
            while (loopFileNameAgain == true)
            {
               std::cout << "> ";
               try
               {
                  std::getline(std::cin, fileName);
                  if (std::cin.eof())
                  {
                     loopFileNameAgain = false;
                     std::cout << std::endl;
                     printQuitMessage();
                  }
                  else if (loadGame(fileName))
                  {
                     // loadGame() function now only checks if the filename is
                     // valid might change to actually call playGame() as well
                     // but that would leave this else if essentially blank
                     std::ifstream savedGame(fileName + ".save");
                     Game* game = new Game(2, savedGame);
                     game->playGame();
                     loopFileNameAgain = false;
                  }
                  else
                  {
                     throw std::invalid_argument("Invalid Input");
                  }
               }
               catch (std::invalid_argument& e)
               {
                  std::cout << e.what() << std::endl;
               }
            }
         }
         else if (input == CREDITS)
         {
            std::cout << std::endl;
            printCredits();
            printMenu();
         }
         else if (input == QUIT)
         {
            printQuitMessage();
            loopAgain = false;
         }
         else if (std::cin.eof())
         {
            loopAgain = false;
            std::cout << std::endl;
            printQuitMessage();
         }
         else
         {
            throw std::invalid_argument("Invalid Input");
         }
      }
      catch (std::invalid_argument& e)
      {
         std::cout << e.what() << std::endl;
      }
   }
   return EXIT_SUCCESS;
}

bool loadGame(std::string fileName)
{
   bool isValidFile = false;
   // Need to validate file here (check the spec)
   // try catch?
   std::ifstream savedGame(fileName + ".save");

   if (savedGame.good())
   {
      // hard coded 2 players will need to be changed in individual enhancements
      // Game* game = new Game(2, savedGame);
      isValidFile = true;
   }
   return isValidFile;
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
   std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;
}