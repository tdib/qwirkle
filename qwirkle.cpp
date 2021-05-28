#include "Game.hpp"
#include "InputCodes.hpp"
#include "LinkedList.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#define MIN_PLAYERS 2
#define MAX_PLAYERS 4

// print the menu options
void printMenu();
// print the student credits
void printCredits();
// utility method - used to format a student name and id
void printStudent(std::string name, std::string id);
// say goodbye to the user
void printQuitMessage();
// check if a given file exists and can be accessed
bool isValidFile(std::string fileName);
// check if given input is a numeric value
bool isNumeric(std::string str);

// INDIVIDUAL

// get count of players (2-4)
int getNumPlayers();
// function for beginning a new game
void newGameCommand();
// function for getting a save file name from the user
bool loadGameCommand();
// toggle whether tiles are shown in colour or not and inform the user
void toggleTileColour();
// determines if the game will be printed in colour or white
bool colourPrinting;
// now placed here due to returning to the menu
Game* game;
// determines if the player has attempted to terminate the game
bool hasQuit;

int main(void)
{
   // print intro text
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;

   // loop until the user has quit or an eof character is detected
   std::string input = "";
   hasQuit           = false;
   colourPrinting    = false;
   while (!hasQuit)
   {
      try
      {
         // print menu and prompt for user input
         printMenu();
         std::cout << "> ";
         std::getline(std::cin, input);

         // user presses 1 to begin new game
         if (input == NEW_GAME)
         {
            newGameCommand();
         }
         // user presses 2 to load game
         else if (input == LOAD_GAME)
         {
            input          = "";
            bool loopAgain = true;
            while (loopAgain == true)
            {
               loopAgain = loadGameCommand();
            }
         }
         // user presses 3 to display student credits
         else if (input == CREDITS)
         {
            std::cout << std::endl;
            printCredits();
         }
         // user presses 4 to quit the game
         else if (input == QUIT)
         {
            hasQuit = true;
            printQuitMessage();
         }
         // user presses 5 to toggle whether tile colours are displayed or not
         else if (input == TOGGLE_COLOUR)
         {
            toggleTileColour();
         }
         // end of file character detected
         else if (std::cin.eof())
         {
            hasQuit = true;
            std::cout << std::endl;
            printQuitMessage();
         }
         else
         {
            throw std::invalid_argument(
               "Please select a valid option (1-5 inclusive).\n");
         }
      }
      catch (std::invalid_argument& e)
      {
         std::cout << e.what() << std::endl;
      }
   }
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
         // make sure user input consists of only integers
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
         // eof character detected
         else if (std::cin.eof())
         {
            eofChar = true;
            printQuitMessage();
         }
         // non integer value
         else
         {
            throw std::invalid_argument("Please enter an integer value.");
         }
      }
      catch (const std::invalid_argument& e)
      {
         std::cout << e.what() << std::endl;
      }
   } while ((!isNumeric(numPlayersStr) || !isValidNumber) && (!eofChar));

   return numPlayers;
}

void newGameCommand()
{
   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   // create a game, takes in the number of players which is calculated
   // by getNumPlayers(), and whether colour is enabled
   game    = new Game(getNumPlayers(), colourPrinting);
   hasQuit = game->playGame();
   delete game;
   // if an eof character is detected - say goodbye and close game
   if (std::cin.eof())
   {
      printQuitMessage();
      hasQuit = true;
   }
}

bool loadGameCommand()
{
   std::string userInput = "";
   std::cout << std::endl;
   std::cout << "Enter the filename from which to load a game" << std::endl;

   // loop until a proper file is received
   bool loopAgain = true;
   try
   {
      std::cout << "> ";
      std::getline(std::cin, userInput);
      if (std::cin.eof())
      {
         hasQuit   = true;
         loopAgain = false;
         std::cout << std::endl;
         printQuitMessage();
      }
      // check if entered file exists
      else if (isValidFile(userInput))
      {
         // load into game
         std::ifstream savedGame(userInput + ".save");
         game      = new Game(savedGame, colourPrinting);
         loopAgain = false;
         hasQuit   = game->playGame();
         delete game;

         if (std::cin.eof())
         {
            printQuitMessage();
            hasQuit = true;
         }
      }
      // if the entered file does not exist
      else
      {
         // check if the user input was cancel
         std::transform(
            userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
         if (userInput == CANCEL)
         {
            // stop prompting user for input (return to menu)
            loopAgain = false;
            std::cout << std::endl;
         }
         // entered file does not exist and input was not cancel
         else
         {
            throw std::invalid_argument(
               "Please enter a relative path to a file");
         }
      }
   }
   catch (std::invalid_argument& e)
   {
      std::cout << e.what() << std::endl;
   }
   return loopAgain;
}

void toggleTileColour()
{
   // toggle tile colour
   colourPrinting = !colourPrinting;
   if (!colourPrinting)
   {
      std::cout << "The colours of the tiles have been turned off." << std::endl
                << std::endl;
   }
   else
   {
      std::cout << "The colours of the tiles will now be shown." << std::endl
                << std::endl;
   }
}