#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#ifndef ADDONS_H
#define ADDONS_H
using namespace sf;
using namespace std;
class Addon
{     protected:
      Texture tex;
      Sprite sprite;
      bool active = false;
      string type;
public:
      virtual void drawAddon() = 0;
      virtual void moveAddon() = 0;
      virtual Sprite getSprite() = 0;
      virtual string getType()=0;
      virtual void setType(string)=0;
      virtual void setActive(bool a)=0;
      virtual bool getActive()=0;
      virtual void resetPosition(float, float)=0;
      virtual bool isDodged()=0;
      virtual void setDodged(bool)=0;
      
};

#endif