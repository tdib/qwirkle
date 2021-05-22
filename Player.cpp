#include "Player.hpp"

Player::Player()
    : bag(nullptr)
    , board(nullptr)
    , hand(new LinkedList())
    , name("")
    , score(0)
    , AIStatus(false)
{
}

Player::Player(std::string playerName, int playerScore, std::string playerHand,
   bool AIStatus)
    : bag(nullptr)
    , board(nullptr)
    , hand(new LinkedList())
    , name(playerName)
    , score(playerScore)
{
   this->setHand(playerHand);
   this->setAIStatus(AIStatus);
}

Player::~Player()
{
   while (!hand->isEmpty())
   {
      delete hand->pop();
   }

   delete hand;
}

void Player::setHand(std::string newHand)
{
   // create stringstream and iterate through, adding each tile to hand
   std::stringstream handTiles(newHand);
   while (handTiles.good())
   {
      std::string currTile = "";
      std::getline(handTiles, currTile, ',');
      Colour tileColour     = currTile[0];
      std::string toConvert = "";
      toConvert.push_back(currTile[1]);
      Shape tileShape = atoi(toConvert.c_str());

      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

      // check if tile is valid
      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            if (tileShape == shape && tileColour == colour)
            {
               this->hand->push(new Tile(tileShape, tileColour));
            }
         }
      }
   }
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
   bool canDraw = false;
   if (!bag->getTilesInBag()->isEmpty())
   {
      canDraw         = true;
      Tile* drawnTile = nullptr;

      drawnTile = bag->popTile();
      hand->push(drawnTile);
   }

   return canDraw;
}

bool Player::swapTile(std::string tileToSwap)
{
   bool matchingTile = false;
   int tileIndex     = hand->findTileIndex(tileToSwap);

   if (tileIndex != -1)
   {
      Tile* tempTile = hand->grab(tileIndex);
      bag->pushTile(tempTile);
      drawTile();

      matchingTile = true;
   }

   return matchingTile;
}

void Player::setAIStatus(bool AIStatus)
{
   this->AIStatus = AIStatus;
}

bool Player::getAIStatus()
{
   return this->AIStatus;
}

void Player::addScore(int score)
{
   this->score += score;
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

std::string Player::getHandStr()
{
   return hand->getContents();
}

bool Player::isEmptyHand()
{
   return hand->isEmpty();
}

bool Player::tileInHand(std::string tileToValidate)
{
   return (hand->findTileIndex(tileToValidate) != -1);
}

Tile* Player::getTileFromHand(std::string tileToGet)
{
   Tile* tempTile = nullptr;
   int tileIndex  = hand->findTileIndex(tileToGet);

   if (tileIndex != -1)
   {
      tempTile = hand->grab(tileIndex);
   }

   return tempTile;
}

void Player::addToHand(Tile* tile)
{
   hand->push(tile);
}

LinkedList* Player::getHand()
{
   return hand;
}