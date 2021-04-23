#include "LinkedList.h"
#include "Game.h"

#include <iostream>
#include <exception>
#include <string>

void printMenu();
void printCredits();
void printStudent(std::string name, std::string id);
void printQuitMessage();
bool isValidName(std::string name);

int main(void) {

   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::cout << std::endl;
   bool validInput=false;
   std::string input;
   printMenu();
   while(validInput==false)
   {
      std::getline(std::cin, input);
      if(input=="1")
      {
         validInput = true;
         std::cout << std::endl;
         std::cout << "Starting a New Game" << std::endl;
         std::cout << std::endl;

         std::string player1Name=" ";
         std::string player2Name=" ";

         while(!isValidName(player1Name)&&!std::cin.eof())
         {
         std::cout << 
            "Enter a name for player 1 (uppercase characters only, no spaces)"
            << std::endl;
         std::cout << "> ";
         std::getline(std::cin, player1Name);
         }

         while(!isValidName(player2Name)&&!std::cin.eof())
         {
         std::cout << 
            "Enter a name for player 2 (uppercase characters only, no spaces)"
            << std::endl;
         std::cout << "> ";
         std::getline(std::cin, player2Name);
         }

         std::cout << "Let's Play!" << std::endl;
      }
      if(input=="2")
      {
         validInput = true;
         std::cout << std::endl;
         std::cout << "Enter the filename from which load a game" << std::endl;
         std::cout << "> ";
         // get file and validate
         // if valid
         std::cout << std::endl;
         std::cout << "Qwirkle game successfully loaded" << std::endl;
         //spec doesn't say what to do if invalid.
      }   
      if(input=="3")
      {
         validInput = true;
         std::cout << std::endl;
         printCredits();
      }   
      if(input=="4")
      {  
         validInput = true;
         std::cout << std::endl;
         printQuitMessage();
      }   
      if(std::cin.eof())
      {
         validInput = true;
         printQuitMessage();
      }
      if(validInput ==false)
      {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
      }
      // temp to make it go back to main menu after showing credits.
      if(input=="3")
      {
         validInput = false;
         printMenu();
      }

   }

   std::cout << "Test - Reading from tiles.txt" << std::endl;
   Game* game = new Game();

   try {
      game->initialiseTiles();
   } catch (std::exception& e) {
      return EXIT_FAILURE;
   }

   std::cout << "Test - Printing board state" << std::endl;
   game->printState();
   
   // Where do I put this game input loop in Game.cpp :(
   // Should it be here? In qwirkle.cpp?
   std::cout << "Test - Game Input Loop" << std::endl;

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

   delete game;

   return EXIT_SUCCESS;

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
// returns false if there is a lower case letter.
bool isValidName(std::string name)
{
   int length = name.length();
   bool isValid = true;
   for(int i =0; i<length; i++)
   {
      if(!isupper(name[i]))
      {
       isValid =false;  
      }
   }
   return isValid;
}
