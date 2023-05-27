#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef BOMB_H
#define BOMB_H
using namespace sf;
using namespace std;
class Bomb
{
      Texture tex;
      bool active = false, assigned = false;
public:
      Sprite sprite;
      void setActive(bool a) { active = a; }
      bool getActive() { return active; }
      bool getAssigned() { return assigned; }
      void setAssigned(bool a) { assigned = a; }
      void drawBomb(float x, float y, string path)
      {
            tex.loadFromFile(path);
            sprite.setTexture(tex);
            sprite.setPosition(x + 20, y + 5);
            sprite.setScale(0.5, 0.5);
      }
      Sprite getSprite() { return sprite; }
      void moveBomb(float x, float y)
      {
            
            sprite.move(x, y);
      }
};
#endif