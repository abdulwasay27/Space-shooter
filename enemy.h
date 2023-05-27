#include <SFML/Graphics.hpp>
#include <iostream>
#include "bomb.h"
#ifndef ENEMY_H
#define ENEMY_H
using namespace sf;
using namespace std;
class Enemy
{
protected:
      int killScore;
      float dropTime;
      Texture tex;
      Sprite sprite;

public:
      Bomb *bomb;
      virtual void drawEnemy(float, float) = 0;
      virtual void moveEnemy() = 0;
      virtual Sprite getSprite() = 0;
      virtual bool detectBulletCollision(float, float) = 0;
      virtual bool getActive() const = 0;
      virtual void setActive(bool) = 0;
      virtual void setBomb(Bomb *) = 0;
      virtual void setDropTime(float) = 0;
      virtual float getDropTime() = 0;
      virtual void setKillScore(int) = 0;
      virtual int getKillScore() = 0;
      virtual bool getBombActive() = 0;
      virtual void setBombActive(bool) = 0;
      virtual bool getDodgeMonster()=0;
      virtual void setDodgeMonster(bool)=0;
      virtual ~Enemy()
      {
            // cout<<"IN ENEMY"<<endl;
      }
};
#endif