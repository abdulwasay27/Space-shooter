#include <SFML/Graphics.hpp>
#include "invader.h"
#include <iostream>
using namespace std;
using namespace sf;
class alphaInvader : public Invader
{

      bool active = true, bombActive = false;
      int noBombs = 0;

public:
      void drawEnemy(float x, float y)
      {
            tex.loadFromFile("img/enemy_1.png");
            sprite.setTexture(tex);
            sprite.setPosition(x, y);
            sprite.setScale(0.5, 0.5);
            setKillScore(10);
      }
      
      Sprite getSprite() { return sprite; }
      void setKillScore(int k = 10) { killScore = k; }
      int getKillScore() { return killScore; }
      void setActive(bool a) { active = a; }
      bool getActive() const { return active; }
      void setBomb(Bomb *bomb)
      {
            this->bomb = bomb;
      }
      void setDropTime(float time) { dropTime = time; }
      float getDropTime() { return dropTime; }
      bool getBombActive() { return bombActive; }
      void setBombActive(bool a) { bombActive = a; }

      virtual ~alphaInvader()
      {
            
      }
};
