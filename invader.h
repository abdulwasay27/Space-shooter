#include <SFML/Graphics.hpp>
#include "enemy.h"
#ifndef INVADER_H
#define INVADER_H
using namespace sf;
class Invader : public Enemy
{
      
public:
      bool detectBulletCollision(float x, float y)
      {
            // the .left returns the starting position of the container and the .width returns the right most x coordinate of the sprite
            // the .top returns top left position of the container which checks that the bullet does not go above.
            // The .right gives the height of the sprite itself and it checks the bottom bounds
            if ((x >= this->getSprite().getGlobalBounds().left && x <= this->getSprite().getGlobalBounds().left + this->getSprite().getGlobalBounds().width - 2) &&
                (y >= this->getSprite().getGlobalBounds().top && y <= this->getSprite().getGlobalBounds().top + this->getSprite().getGlobalBounds().height - 2))
            {
                  return true;
            }
            return false;
      };
      void moveEnemy() {}
      virtual bool getDodgeMonster() { return 0; }
      virtual void setDodgeMonster(bool ) {  }

};
#endif