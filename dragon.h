#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <iostream>
using namespace std;
using namespace sf;
class Dragon : public Enemy
{
      Texture tex;
      Sprite sprite;
      bool active = false;

public:
      void drawEnemy(float x, float y)
      {
            tex.loadFromFile("img/dragon.png");
            sprite.setTexture(tex);
            sprite.setPosition(x, y+45);
            sprite.setScale(1, 1);
            setKillScore(50);
      }
      void moveEnemy()
      {
      }
      Sprite getSprite() { return sprite; }
      bool detectBulletCollision(float, float) { return 0; }
      bool getActive() const { return active; }
      void setActive(bool a) { active = a; }
      void setBomb(Bomb *objs) { bomb = objs; }
      void setDropTime(float){};
      float getDropTime() { return 0.0; }
      void setKillScore(int k = 50) { killScore = k; }
      int getKillScore() { return killScore; }
      bool getBombActive() { return 0; }
      void setBombActive(bool) {}
      bool getDodgeMonster() { return 0; }
      void setDodgeMonster(bool ) {  }
};