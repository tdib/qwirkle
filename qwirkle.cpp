#include "Game.hpp"
#include "InputCodes.hpp"
#include "LinkedList.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#define MIN_PLAYERS 2
#define MAX_PLAYERS 4

void printMenu();
void printCredits();
void printStudent(std::string name, std::string id);
void printQuitMessage();
bool isValidFile(std::string fileName);
bool isNumeric(std::string str);

// INDIVIDUAL
// get count of players (2-4)
int getNumPlayers();
// determines if the game will be printed in colour or white
bool colourPrinting;
Game* game;

int main(void)
{
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;
   bool loopAgain    = true;
   std::string input = "";
   colourPrinting    = false;
   while (loopAgain == true)
   {
      printMenu();
      std::cout << "> ";
      try
      {
         std::getline(std::cin, input);
         if (input == NEW_GAME)
         {
            // loopAgain = false;
            std::cout << std::endl;
            std::cout << "Starting a New Game" << std::endl;
            std::cout << std::endl;

            // Create a game. Takes in the number of players
            // which is calculated by getNumPlayers()
            game = new Game(getNumPlayers(), colourPrinting);
            game->playGame();
            delete game;
            if (std::cin.eof())
            {
               printQuitMessage();
            }
         }
         else if (input == LOAD_GAME)
         {
            // loopAgain            = false;
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
                  else if (isValidFile(fileName))
                  {
                     std::ifstream savedGame(fileName + ".save");
                     // Game* game = new Game(savedGame);
                     game = new Game(savedGame, colourPrinting);
                     game->playGame();
                     delete game;
                     loopFileNameAgain = false;

                     if (std::cin.eof())
                     {
                        printQuitMessage();
                     }
                  }
                  else
                  {
                     throw std::invalid_argument(
                        "Please enter a relative path to a file");
                  }
               }
               catch (std::invalid_argument& e)
               {
                  std::cerr << e.what() << '\n';
               }
            }
         }
         else if (input == CREDITS)
         {
            std::cout << std::endl;
            printCredits();
            // printMenu();
         }
         else if (input == QUIT)
         {
            printQuitMessage();
            loopAgain = false;
         }
         else if (input == TOGGLE_COLOUR)
         {
            if (colourPrinting)
            {
               colourPrinting = false;
               std::cout << "The colours of the tiles have been turned off."
                         << std::endl
                         << std::endl;
            }
            else
            {
               colourPrinting = true;
               std::cout << "The colours of the tiles will now be shown."
                         << std::endl
                         << std::endl;
            }
            // printMenu();
         }
         else if (std::cin.eof())
         {
            loopAgain = false;
            std::cout << std::endl;
            printQuitMessage();
         }
         else
         {
            throw std::invalid_argument(
               "Please select a valid option (1-5 inclusive).");
         }
      }
      catch (std::invalid_argument& e)
      {
         std::cout << e.what() << std::endl;
      }
   }
   // delete game;
   return EXIT_SUCCESS;
}

bool isValidFile(std::string fileName)
{
   bool isValidFile = false;
   std::ifstream savedGame(fileName + ".save");

   if (savedGame.good())
   {
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
   std::cout << "5. Toggle tile colours";
   if (colourPrinting)
   {
      std::cout << " [ON]" << std::endl;
   }
   else
   {
      std::cout << " [OFF]" << std::endl;
   }
   std::cout << std::endl;
}

void printCredits()
{
   std::cout << "----------------------------------" << std::endl << std::endl;
   printStudent("Martin Krisnanto Putra", "3608646");
   printStudent("Riley James Gozzard", "3811315");
   printStudent("Ryan Iem", "3700995");
   printStudent("Thomas Joseph Dib", "3838765");
   std::cout << "----------------------------------" << std::endl << std::endl;
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

bool isNumeric(std::string str)
{
   bool isNumeric = true;
   for (char c : str)
   {
      if (!isdigit(c))
      {
         isNumeric = false;
      }
   }
   return isNumeric;
}

int getNumPlayers()
{
   // prompt user for how many players are playing
   std::string numPlayersStr = "";
   int numPlayers            = 0;
   bool isValidNumber        = false;
   bool eofChar              = false;
   std::cout << "How many players are playing?" << std::endl;
   do
   {
      std::cout << "> ";
      std::getline(std::cin, numPlayersStr);
      try
      {
         // if user input consists of only integers
         if (isNumeric(numPlayersStr) && numPlayersStr.length() > 0)
         {
            // convert string to integer and validate the number of players
            numPlayers = std::stoi(numPlayersStr);
            isValidNumber =
               (numPlayers >= MIN_PLAYERS && numPlayers <= MAX_PLAYERS);
            if (!isValidNumber)
            {
               throw std::invalid_argument(
                  "Please choose a number between 2-4 (inclusive).");
            }
         }
         else if (std::cin.eof())
         {
            eofChar = true;
            printQuitMessage();
         }
         else
         {
            throw std::invalid_argument("Please enter an integer value.");
         }
      }
      catch (const std::invalid_argument& e)
      {
         std::cerr << e.what() << '\n';
      }
   } while ((!isNumeric(numPlayersStr) || !isValidNumber) && (!eofChar));

   return numPlayers;
}