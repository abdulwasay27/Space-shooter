#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "addons.h"
#include <string.h>
#include <iostream>
using namespace std;
using namespace sf;
class Player
{
	int lives = 0, numBullets = 0, x = 0, y = 0;
	float score = 0;
	bool destroyable = true, shieldActive = false;

public:
	Bullet *bullets;
	Addon *addon;
	Texture tex, tex1, tex2, shieldTex;
	Sprite sprite, shield;
	float speed = 0.3;

	Player(std::string png_path)
	{

		tex.loadFromFile(png_path);
		tex1.loadFromFile("img/playership_135.png");
		tex2.loadFromFile("img/playership_45.png");
		sprite.setTexture(tex);
		shieldTex.loadFromFile("img/PNG/Effects/shield3.png");
		shield.setTexture(shieldTex);
		x = 340;
		y = 700; // starting positions
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);
		shield.setScale(1, 1);
		addon = nullptr;
	}
	void restart()
	{
		sprite.setPosition(x, y + 30);
		addon = nullptr;
	}

	void setShield(bool a) { shieldActive = a; }
	bool getShield() { return shieldActive; }
	void setNumBullets(int n) { numBullets = n; }
	int getNumBullets() { return numBullets; }
	void setBullets(Bullet *obj)
	{
		bullets = obj;
	}
	void setScore(float s)
	{
		score += s;
	}
	bool getDestroyable() { return destroyable; }
	void setDestroyable(bool a) { destroyable = a; }
	float getScore() { return score; }
	int getLives() { return lives; }
	void setLives(int n) { lives += n; }
	void resetLives(int n) { lives = n; }
	Sprite getSprite() { return sprite; }
	void setAddon(Addon *obj) { addon = obj; }
	void resetPlayer(int n)
	{
		lives=n;
		shieldActive=false;
		destroyable=true;
		score=0;
		sprite.setPosition(x,y);
		bullets->reset();
	}
	void fireBullet()
	{

		for (int i = 0; i < numBullets; i++)
		{

			if (!bullets[i].active)
			{
				bullets[i].sprite.setPosition(sprite.getPosition().x + 30, sprite.getPosition().y - 40);
				bullets[i].active = true;
				break;
			}
		}
	}
	void updateBullets()
	{
		for (int i = 0; i < numBullets; i++)
		{
			if (bullets[i].active)
			{

				bullets[i].update();
			}
		}
	}
	float getBulletCoordinateX(int index)
	{
		return bullets[index].sprite.getPosition().x;
	}
	float getBulletCoordinateY(int index)
	{
		return bullets[index].sprite.getPosition().y;
	}
	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		bool diagonal = false;
		if (s == "l")
		{
			delta_x = -1;
		}
		else if (s == "r")
			delta_x = 1;
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;
		else if (s == "ld")
		{
			diagonal = true;
			sprite.setTexture(tex1);
			delta_x = -1;
			delta_y = -1;
		}
		else if (s == "rd")
		{
			diagonal = true;
			sprite.setTexture(tex2);
			delta_x = 1;
			delta_y = -1;
		}
		else if (s == "bld")
		{
			diagonal = true;
			sprite.setTexture(tex2);
			delta_x = -1;
			delta_y = 1;
		}
		else if (s == "brd")
		{
			diagonal = true;
			sprite.setTexture(tex1);
			delta_x = 1;
			delta_y = 1;
		}
		if (!diagonal)
		{
			sprite.setTexture(tex);
		}
		delta_x *= speed;
		delta_y *= speed;
		if (sprite.getPosition().x < 0)
			sprite.setPosition(750, sprite.getPosition().y);
		if (sprite.getPosition().x > 750)
			sprite.setPosition(0, sprite.getPosition().y);
		if (sprite.getPosition().y < 0)
			sprite.setPosition(sprite.getPosition().x, 730);
		if (sprite.getPosition().y > 750)
			sprite.setPosition(sprite.getPosition().x, 0);
		if (sprite.getPosition().x == 0 && sprite.getPosition().y == 0)
			sprite.setPosition(700, 0);
		if (sprite.getPosition().x > 700 && sprite.getPosition().y > 700)
			sprite.setPosition(0, 0);
		if (sprite.getPosition().x > 700 && sprite.getPosition().y < 2)
			sprite.setPosition(0, 700);
		if (sprite.getPosition().x < 2 && sprite.getPosition().y > 700)
			sprite.setPosition(700, 0);

		sprite.move(delta_x, delta_y);
	}
	void setShieldPosition()
	{
		shield.setPosition(sprite.getPosition().x - 30, sprite.getPosition().y - 20);
	}
};
