#include <SFML/Graphics.hpp>
#include "invader.h"
#include <iostream>
using namespace std;
using namespace sf;
class betaInvader : public Invader
{

      bool active = true, bombActive = false;

public:
      void drawEnemy(float x, float y)
      {
            tex.loadFromFile("img/enemy_2.png");
            sprite.setTexture(tex);
            sprite.setPosition(x, y);
            sprite.setScale(0.5, 0.5);
            setKillScore(20);
      }
      void moveEnemy() {}
      Sprite getSprite() { return sprite; }

      void setActive(bool a) { active = a; }
      bool getActive() const { return active; }
      void setBomb(Bomb *bomb)
      {
            this->bomb = bomb;
      }
      void setKillScore(int k = 20) { killScore = k; }
      int getKillScore() { return killScore; }
      void setDropTime(float time) { dropTime = time; }
      float getDropTime() { return dropTime; }
      bool getBombActive() { return bombActive; }
      void setBombActive(bool a) { bombActive = a; }
      virtual ~betaInvader()
      {
           
      }
};
