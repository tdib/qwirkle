#include "Player.hpp"

Player::Player()
    : bag(nullptr)
    , board(nullptr)
    , hand(new LinkedList())
    , name("")
    , score(0)
{
}

Player::Player(std::string playerInfo)
{
   /**
    * playeronename
    * playeronescore
    * playeronehand
    */

   std::string newName = "";
   // this->setName(std::getline(playerInfo, newName));
}

Player::~Player()
{
   delete hand;
}

void Player::setBag(Bag* bag)
{
   this->bag = bag;
}

void Player::setBoard(Board* board)
{
   this->board = board;
}

bool Player::drawTile()
{
   return false;
}

bool Player::placeTile(Tile* tile, std::string coordinate)
{
   return false;
}

bool Player::swapTile(Tile* tileToSwap)
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
   return "";
}

bool Player::isEmptyHand()
{
   return hand->isEmpty();
}