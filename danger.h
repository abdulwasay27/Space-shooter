#include <SFML/Graphics.hpp>
#include <iostream>
#include "addons.h"
using namespace sf;
using namespace std;
class Danger : public Addon
{
      bool dodged = false;

public:
      void drawAddon()
      {
            tex.loadFromFile("img/PNG/Power-ups/powerupRed.png");
            sprite.setTexture(tex);
            sprite.setPosition(60, 0);
            sprite.setScale(1, 1);
      }
      void moveAddon()
      {
            if (sprite.getPosition().y > 750)
            {
                  active = false;
                  dodged = true;
            }
            else
                  sprite.move(0, 0.1);
      }

      void setActive(bool a) { active = a; }
      bool getActive() { return active; }
      Sprite getSprite()
      {
            return sprite;
      }
      void resetPosition(float x, float y)
      {
            sprite.setPosition(x, y);
      }
      void setType(string s) { type = s; }
      string getType() { return type; }
      bool isDodged() { return dodged; }
      void setDodged(bool a) { dodged = a; }
};