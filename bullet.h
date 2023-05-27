#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#ifndef BULLET_H
#define BULLET_H
using namespace sf;
using namespace std;
class Bullet
{
public:
	bool active;
	bool isActive() { return active; }
	void setActive(bool a) { active = a; }
	Texture tex;
	Sprite sprite;
	Bullet()
	{
		active = false;
		tex.loadFromFile("img/PNG/Effects/fire11.png");
		sprite.setTexture(tex);
		sprite.setScale(1, 2);
	}
	void update()
	{
		sprite.move(0, -1);
		if (sprite.getPosition().y < 50)
		{
			active = false;
		}
	}
	void reset()
	{
		sprite.setTexture(tex);
	}
	void setNewTexture(string path)
	{
		
		tex.loadFromFile(path);
		sprite.setTexture(tex);
		sprite.setScale(1, 2);
	}
};
#endif