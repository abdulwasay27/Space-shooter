#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <iostream>
using namespace std;
using namespace sf;
class Monster : public Enemy
{
      Texture tex;
      Sprite sprite;
      bool active = false, changeDirection = false, dodgeMonster = true;

public:
      void drawEnemy(float x, float y)
      {
            tex.loadFromFile("img/monster.png");
            sprite.setTexture(tex);
            sprite.setPosition(x, y+30);
            sprite.setScale(0.1, 0.1);
      }
      void moveEnemy()
      {

            if (this->sprite.getPosition().x <= 50)
                  changeDirection = false;

            else if (this->sprite.getPosition().x >= 450)
                  changeDirection = true;
            // changeDirection variable is the only used to control the direction of monster
            // when it is false, the first case runs. when it is true, the second case runs
            if (this->sprite.getPosition().x < 450 && !changeDirection)
            {
                  sprite.move(0.1, 0);
            }
            else if (this->sprite.getPosition().x > 30 && changeDirection)
            {
                  sprite.move(-0.1, 0);
            }
            setKillScore(40);
      }
      Sprite getSprite() { return sprite; }
      bool detectBulletCollision(float, float) { return 0; }
      bool getActive() const { return active; }
      void setActive(bool a) { active = a; }
      void setKillScore(int k = 40) { killScore = k; }
      int getKillScore() { return killScore; }
      void setBomb(Bomb *obj) { bomb = obj; }
      void setDropTime(float){};
      float getDropTime() { return 0.0; }
      bool getDodgeMonster() { return dodgeMonster; }
      void setDodgeMonster(bool a) { dodgeMonster = a; }
      bool getBombActive() { return 0; }
      void setBombActive(bool) {}
};