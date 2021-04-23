#include "Player.h"
#include <string>
#include <iostream>

Player::Player(Bag* bag, Board* board)
{
   this->bag = bag;
   this->board = board;
   this->score = 0;
}

Player::Player(std::string playerInfo)
{
   /**
    * playeronename
    * playeronescore
    * playeronehand
    * 
    */

   std::string newName = "";
   // this->setName(std::getline(playerInfo, newName));

}

bool Player::drawTile()
{
   return false;
}

bool Player::placeTile(Tile* tile, std::string coordinate)
{
   return false;
}

bool Player::swapTile()
{
   
   return false;
}

void Player::addScore()
{

}

std::string Player::getName()
{
   return this->name;
}

void Player::setName(std::string newName)
{
   this->name = newName;
}

int Player::getScore()
{
   return this->score;
}

std::string Player::getHand()
{

}

