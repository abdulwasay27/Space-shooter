#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "menu.h"
#include "bullet.h"
#include "addons.h"
#include "powerup.h"
#include "fire.h"
#include "lives.h"
#include "danger.h"
#include "player.h"
#include "bomb.h"
#include "enemy.h"
#include "invader.h"
#include "monster.h"
#include "dragon.h"
#include "alphaInvader.h"
#include "betaInvader.h"
#include "gammaInvader.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace std;
using namespace sf;

class Game
{
    // this structure will store the player data
    struct playerData
    {
        string name;
        string score;
    } *data;

public:
    Sprite background; // Game background sprite
    Texture bg_texture;
    Player *p; // player
    Bullet *bullets;
    int noPlayers = 0, noLives = 3, noBullets = 20, bulletTime = 0, noInvaders = 8, noBombs = 20,
        noAddons = 4, maxcurrentBombTime = 0, maxMonsterTime = 0, maxDragonTime = 0, level = 1,
        phase = 1;
    string scores[3], name;
    Addon *addons[4];
    Enemy *invaders[12] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    Bomb *bombs, *monsterBomb, *dragonBombs;
    Enemy *monster;
    Enemy *dragon;
    string invaderAmmoPath = "img/PNG/Lasers/laserRed08.png";
    string monsterAmmoPath = "img/PNG/Lasers/laserRed14.png";
    string originalBulletPath = "img/PNG/Effects/fire11.png";
    string fireAddonPath = "img/PNG/Lasers/laserGreen04.png";
    string powerupAddonPath = "img/PNG/Lasers/laserBlue04.png";
    Font scorefont;
    Text nameInput, currentScore, highscore1, highscore2, highscore3, lives;
    SoundBuffer  fireBulletBuffer;
    Music music;
    Sound fireBulletSound;
    Menu menu;
    Game()
    {
        bullets = new Bullet[noBullets];
        bombs = new Bomb[noBombs];

        // creating the monster, assiging it a bomb, setting position of its bomb
        monster = new Monster();
        monsterBomb = new Bomb();
        monster->setBomb(monsterBomb);
        monster->setActive(false);
        monster->drawEnemy(300, 50);

        // creating the dragon, assiging it bombs, setting position of its bombs
        dragonBombs = new Bomb[3];
        dragon = new Dragon();
        dragon->setBomb(dragonBombs);
        dragon->drawEnemy(270, 20);
        dragon->bomb[0].drawBomb(dragon->getSprite().getPosition().x + 93, dragon->getSprite().getPosition().y + 210, "img/PNG/Lasers/laserBlue00.png");
        dragon->bomb[1].drawBomb(dragon->getSprite().getPosition().x - 140, dragon->getSprite().getPosition().y + 230, "img/PNG/Lasers/laserBlue00_left.png");
        dragon->bomb[2].drawBomb(dragon->getSprite().getPosition().x + 93, dragon->getSprite().getPosition().y + 230, "img/PNG/Lasers/laserBlue00_right.png");
        dragon->bomb[0].setActive(false);
        dragon->bomb[1].setActive(false);
        dragon->bomb[2].setActive(false);

        // creating the addons
        addons[0] = new PowerUp();
        addons[0]->drawAddon();
        addons[0]->setType("powerup");
        addons[1] = new Fire();
        addons[1]->drawAddon();
        addons[1]->setType("fire");
        addons[2] = new Lives();
        addons[2]->drawAddon();
        addons[2]->setType("lives");
        addons[3] = new Danger();
        addons[3]->drawAddon();
        addons[3]->setType("danger");

        p = new Player("img/player_ship.png");
        p->setNumBullets(noBullets);
        p->setBullets(bullets);
        bg_texture.loadFromFile("img/newbackground.png");
        background.setTexture(bg_texture);
        background.setScale(0.71, 0.73);

        // setting the font on screen
        scorefont.loadFromFile("fonts/scorefont1.ttf");
        // setting the formatting of Text objects on screen
        currentScore.setCharacterSize(25);
        currentScore.setPosition({30, 15});
        currentScore.setFont(scorefont);
        currentScore.setFillColor(Color::White);

        lives.setCharacterSize(25);
        lives.setPosition({250, 15});
        lives.setFont(scorefont);
        lives.setFillColor(Color::White);

        highscore1.setCharacterSize(25);
        highscore1.setPosition({420, 15});
        highscore1.setFont(scorefont);
        highscore1.setFillColor(Color::White);

        highscore2.setCharacterSize(25);
        highscore2.setPosition({540, 15});
        highscore2.setFont(scorefont);
        highscore2.setFillColor(Color::White);

        highscore3.setCharacterSize(25);
        highscore3.setPosition({670, 15});
        highscore3.setFont(scorefont);
        highscore3.setFillColor(Color::White);

        music.openFromFile("sounds/background.ogg");
        
        music.setVolume(3);
        music.setLoop(true);

        fireBulletBuffer.loadFromFile("sounds/fire.ogg");
        fireBulletSound.setBuffer(fireBulletBuffer);
        fireBulletSound.setVolume(160);
        
        readInput();
        sortScore();
    }
    // this functino will read the data from the file as well as take user input and store it
    void readInput()
    {
        ifstream inputFile("data/data.txt");
        string input, name, score;
        while (getline(inputFile, input))
        {
            noPlayers++;
            // cout << input << endl;
        }
        noPlayers++;
        data = new playerData[noPlayers];
        inputFile.close();
        inputFile.open("data/data.txt");
        int i = 0;

        while (getline(inputFile, name, ',') && getline(inputFile, score) && i < noPlayers)
        {
            data[i].name = name;
            data[i].score = score;

            i++;
        }
        inputFile.close();
        cout << endl
             << "Enter your name: ";
        cin >> data[noPlayers - 1].name;

        cin.ignore();
    }
    // this function will write data to the file once the game is over
    void writeScore()
    {
        ofstream outputFile("data/data.txt", ios::app);
        outputFile << data[noPlayers - 1].name << ',' << p->getScore() << '\n';
        outputFile.close();
    }
    // this function will sort the scores stored in the structure
    void sortScore()
    {
        string tempName, tempScore;
        for (int i = 0; i < noPlayers - 1; i++)
            for (int j = 0; j < noPlayers - 1 - i; j++)
            {

                if (stringScoreToInt(data[j + 1].score) > stringScoreToInt(data[j].score))
                {
                    tempName = data[j].name;
                    tempScore = data[j].score;
                    data[j].name = data[j + 1].name;
                    data[j].score = data[j + 1].score;
                    data[j + 1].name = tempName;
                    data[j + 1].score = tempScore;
                }
            }
        for (int i = 0; i < 3 && i < noPlayers; i++)
        {
            scores[i] = data[i].score;
            // cout << scores[i] << endl;
        }
    }
    // to convert string scores to integers for calculation
    int stringScoreToInt(string s)
    {
        int n = 0;

        for (int i = 0; i < s.length(); i++)
        {

            n = n * 10 + (s[i] - '0');
        }

        return n;
    }
    // this will decide the current level that the game is operating on, based on the phase
    void decideLevel()
    {
        // if (phase == 4 && level == 3) // means that the game is completed
        // {
        //     restart_game();
        // }
        if (phase == 4) // increase level if phases of the current level are complete
        {
            level++;
            phase = 1;
        }
        //resetting the assigned bombs 
        for(int i=0; i<noBombs; i++)
        bombs[i].setActive(false);
        // Deciding the shapes and the difficulty level of the game basde on the current phase and level
        //  rectangle
        if (phase == 1 && level == 1)
        {
            maxcurrentBombTime = 7;
            maxMonsterTime = 10;
            maxDragonTime = 5;
            noInvaders=8;
            bulletTime = 1;
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(150, 120);
            invaders[0]->setDropTime(5.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 100);
            invaders[1]->setDropTime(3.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(500, 100);
            invaders[2]->setDropTime(2.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(150, 220);
            invaders[3]->setDropTime(3.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(520, 200);
            invaders[4]->setDropTime(3.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(150, 320);
            invaders[5]->setDropTime(5.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 300);
            invaders[6]->setDropTime(3.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(500, 310);
            invaders[7]->setDropTime(2.0);
        }
        // triangle
        else if (phase == 2 && level == 1)
        {

            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(220, 120);
            invaders[0]->setDropTime(5.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 50);
            invaders[1]->setDropTime(3.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(520, 220);
            invaders[2]->setDropTime(2.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(140, 210);
            invaders[3]->setDropTime(3.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(440, 120);
            invaders[4]->setDropTime(3.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(230, 230);
            invaders[5]->setDropTime(5.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 220);
            invaders[6]->setDropTime(3.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(420, 220);
            invaders[7]->setDropTime(2.0);
        }
        // cross
        else if (phase == 3 && level == 1)
        {
            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(180, 70);
            invaders[0]->setDropTime(5.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(280, 150);
            invaders[1]->setDropTime(3.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(450, 350);
            invaders[2]->setDropTime(2.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(260, 270);
            invaders[3]->setDropTime(3.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(450, 60);
            invaders[4]->setDropTime(3.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(380, 150);
            invaders[5]->setDropTime(5.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(380, 250);
            invaders[6]->setDropTime(3.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(160, 350);
            invaders[7]->setDropTime(2.0);
        }
        // circle
        else if (phase == 1 && level == 2)
        {
            maxcurrentBombTime = 5;
            maxMonsterTime = 12;
            maxDragonTime = 5;
            bulletTime = 1.5;
            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(170, 120);
            invaders[0]->setDropTime(4.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 50);
            invaders[1]->setDropTime(2.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(490, 110);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(120, 200);
            invaders[3]->setDropTime(2.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(560, 200);
            invaders[3]->setDropTime(2.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(200, 330);
            invaders[5]->setDropTime(4.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 370);
            invaders[6]->setDropTime(2.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(480, 310);
            invaders[7]->setDropTime(1.0);
        }
        // diamond
        else if (phase == 2 && level == 2)
        {
            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(220, 150);
            invaders[0]->setDropTime(4.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 50);
            invaders[1]->setDropTime(2.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(440, 140);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(130, 240);
            invaders[3]->setDropTime(2.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(530, 240);
            invaders[4]->setDropTime(2.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(220, 360);
            invaders[5]->setDropTime(4.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 430);
            invaders[6]->setDropTime(2.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(440, 360);
            invaders[7]->setDropTime(1.0);
        }
        // heart
        else if (phase == 3 && level == 2)
        {
            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(200, 50);
            invaders[0]->setDropTime(4.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 100);
            invaders[1]->setDropTime(2.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(440, 50);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(130, 190);
            invaders[3]->setDropTime(2.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(530, 190);
            invaders[4]->setDropTime(2.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(200, 310);
            invaders[5]->setDropTime(4.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 400);
            invaders[6]->setDropTime(2.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(440, 300);
            invaders[7]->setDropTime(1.0);
        }
        // filed rectangle
        else if (phase == 1 && level == 3)
        {
            noInvaders = 12;
            maxcurrentBombTime = 3;
            maxMonsterTime = 15;
            maxDragonTime = 10;
            bulletTime = 2;

            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }

            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(150, 120);
            invaders[0]->setDropTime(3.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 100);
            invaders[1]->setDropTime(1.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(500, 100);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(150, 220);
            invaders[3]->setDropTime(1.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(520, 200);
            invaders[4]->setDropTime(1.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(150, 320);
            invaders[5]->setDropTime(3.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 300);
            invaders[6]->setDropTime(1.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(500, 310);
            invaders[7]->setDropTime(1.0);

            invaders[8] = new gammaInvader();
            invaders[8]->drawEnemy(240, 220);
            invaders[8]->setDropTime(1.0);

            invaders[9] = new gammaInvader();
            invaders[9]->drawEnemy(400, 220);
            invaders[9]->setDropTime(1.0);

            invaders[10] = new alphaInvader();
            invaders[10]->drawEnemy(250, 120);
            invaders[10]->setDropTime(3.0);

            invaders[11] = new alphaInvader();
            invaders[11]->drawEnemy(410, 120);
            invaders[11]->setDropTime(3.0);
        }
        // filled diamond
        else if (phase == 2 && level == 3)
        {

            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(220, 150);
            invaders[0]->setDropTime(4.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 50);
            invaders[1]->setDropTime(2.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(440, 140);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(130, 240);
            invaders[3]->setDropTime(2.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(530, 240);
            invaders[4]->setDropTime(2.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(220, 360);
            invaders[5]->setDropTime(4.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 430);
            invaders[6]->setDropTime(2.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(440, 360);
            invaders[7]->setDropTime(1.0);

            invaders[8] = new betaInvader();
            invaders[8]->drawEnemy(270, 200);
            invaders[8]->setDropTime(1.0);

            invaders[9] = new betaInvader();
            invaders[9]->drawEnemy(380, 270);
            invaders[9]->setDropTime(1.0);

            invaders[10] = new alphaInvader();
            invaders[10]->drawEnemy(270, 290);
            invaders[10]->setDropTime(3.0);

            invaders[11] = new alphaInvader();
            invaders[11]->drawEnemy(380, 200);
            invaders[11]->setDropTime(3.0);
        }
        // filled circle
        else if (phase == 3 && level == 3)
        {

            for (int i = 0; i < noInvaders; i++) // deleting the previous invaders
            {
                if (invaders[i] != nullptr)
                    delete invaders[i];
            }
            invaders[0] = new alphaInvader();
            invaders[0]->drawEnemy(170, 120);
            invaders[0]->setDropTime(4.0);

            invaders[1] = new betaInvader();
            invaders[1]->drawEnemy(330, 50);
            invaders[1]->setDropTime(2.0);

            invaders[2] = new gammaInvader();
            invaders[2]->drawEnemy(490, 110);
            invaders[2]->setDropTime(1.0);

            invaders[3] = new betaInvader();
            invaders[3]->drawEnemy(120, 200);
            invaders[3]->setDropTime(2.0);

            invaders[4] = new betaInvader();
            invaders[4]->drawEnemy(560, 200);
            invaders[3]->setDropTime(2.0);

            invaders[5] = new alphaInvader();
            invaders[5]->drawEnemy(200, 330);
            invaders[5]->setDropTime(4.0);

            invaders[6] = new betaInvader();
            invaders[6]->drawEnemy(330, 370);
            invaders[6]->setDropTime(2.0);

            invaders[7] = new gammaInvader();
            invaders[7]->drawEnemy(480, 310);
            invaders[7]->setDropTime(1.0);

            invaders[8] = new betaInvader();
            invaders[8]->drawEnemy(270, 180);
            invaders[8]->setDropTime(1.0);

            invaders[9] = new betaInvader();
            invaders[9]->drawEnemy(400, 270);
            invaders[9]->setDropTime(1.0);

            invaders[10] = new alphaInvader();
            invaders[10]->drawEnemy(270, 290);
            invaders[10]->setDropTime(3.0);

            invaders[11] = new alphaInvader();
            invaders[11]->drawEnemy(400, 180);
            invaders[11]->setDropTime(3.0);
        }
    }
    // this will calculate score based on the input received
    void calculateScore(float points)
    {
        p->setScore(points);
    }
    // bullet collision with an invader
    void detectBulletCollision()
    {
        for (int i = 0; i < p->getNumBullets(); i++)
            if (p->bullets[i].isActive())
            {
                int x = p->getBulletCoordinateX(i), y = p->getBulletCoordinateY(i);
                for (int j = 0; j < noInvaders; j++)
                    if ((invaders[j] != nullptr && invaders[j]->detectBulletCollision(x, y)) && invaders[j]->getActive())
                    {

                        invaders[j]->setActive(false);
                        calculateScore(invaders[j]->getKillScore() * level);
                        if (p->addon != nullptr && p->addon->getType() == "fire")
                            continue;
                        else
                        {
                            p->bullets[i].setActive(false);
                            break;
                        }
                    }
            }
    }

    // player collision with the invader
    bool detectPlayerCollision()
    {

        for (int i = 0; i < noInvaders; i++)
            if (invaders[i] != nullptr && invaders[i]->getActive())
                if ((p->getSprite().getPosition().x >= invaders[i]->getSprite().getGlobalBounds().left && p->getSprite().getPosition().x <= invaders[i]->getSprite().getGlobalBounds().left + invaders[i]->getSprite().getGlobalBounds().width - 2) &&
                    (p->getSprite().getPosition().y >= invaders[i]->getSprite().getGlobalBounds().top && p->getSprite().getPosition().y <= invaders[i]->getSprite().getGlobalBounds().top + invaders[i]->getSprite().getGlobalBounds().height - 2))
                {
                    return true;
                }

        return false;
    }
    // bomb collision with the player
    bool detectBombCollision()
    {
        for (int i = 0; i < noBombs; i++)
        {
            if (bombs[i].getActive())
            {
                if (bombs[i].getSprite().getPosition().x + bombs[i].getSprite().getGlobalBounds().width >= p->getSprite().getGlobalBounds().left &&
                    bombs[i].getSprite().getPosition().x <= p->getSprite().getGlobalBounds().left + p->getSprite().getGlobalBounds().width &&
                    bombs[i].getSprite().getPosition().y + bombs[i].getSprite().getGlobalBounds().height >= p->getSprite().getGlobalBounds().top &&
                    bombs[i].getSprite().getPosition().y <= p->getSprite().getGlobalBounds().top + p->getSprite().getGlobalBounds().height)
                {

                    bombs[i].setActive(false);
                    return true;
                }
            }
        }
        return false;
    }
    // player collision with monster
    bool monsterCollision()
    {
        if (monster->bomb->getActive())
            if (monster->bomb->getSprite().getPosition().x + monster->bomb->getSprite().getGlobalBounds().width >= p->getSprite().getGlobalBounds().left &&
                monster->bomb->getSprite().getPosition().x <= p->getSprite().getGlobalBounds().left + p->getSprite().getGlobalBounds().width)
            {
                p->setLives(-1);
                monster->setDodgeMonster(false);
                return true;
            }
        if ((p->getSprite().getPosition().x >= monster->getSprite().getGlobalBounds().left && p->getSprite().getPosition().x <= monster->getSprite().getGlobalBounds().left + monster->getSprite().getGlobalBounds().width - 2) &&
            (p->getSprite().getPosition().y >= monster->getSprite().getGlobalBounds().top && p->getSprite().getPosition().y <= monster->getSprite().getGlobalBounds().top + monster->getSprite().getGlobalBounds().height - 2))
        {
            p->setLives(-1);
            p->restart();
            return true;
        }
        return false;
    }

    void detectDragonCollision()
    {
    }
    // to check which phase the game is on currently
    bool checkPhase()
    {
        int count = 0;
        
        for (int i = 0; i < noInvaders; i++)
        {

            if (invaders[i] != nullptr && !invaders[i]->getActive()) // to check if all invaders are inactive
                count++;
        }
        if (count == noInvaders-1)
        {
            phase++;
            
            if (phase == 4 && level == 3)
                return true;
            decideLevel();
        }
        return false;
    }
    // to check how many lives the player has left
    bool checkLives()
    {
        if (p->getLives() <= 0)
            return true;
        return false;
    }
    // to assign bombs to the invaders
    void assignBombs(float time)
    {
        bool assigned = false;
        for (int i = 0; i < noInvaders; i++)
        {

            if (invaders[i] != nullptr && invaders[i]->getActive() && !invaders[i]->getBombActive() && time >= invaders[i]->getDropTime())
            {
                for (int j = 0; j < noBombs; j++)
                {
                    if (!bombs[j].getActive() && !bombs[j].getAssigned())
                    {
                        if (invaders[i]->bomb == nullptr)
                        {
                            invaders[i]->setBombActive(true);
                            invaders[i]->setBomb(&bombs[j]);
                            bombs[j].setAssigned(true);
                            bombs[j].setActive(true);
                            assigned = true;
                            invaders[i]->bomb->drawBomb(invaders[i]->getSprite().getPosition().x, invaders[i]->getSprite().getPosition().y, invaderAmmoPath);
                            break;
                        }
                        else if (invaders[i]->bomb != nullptr)
                        {
                            if (!invaders[i]->bomb->getAssigned())
                            {
                                invaders[i]->setBombActive(true);
                                invaders[i]->setBomb(&bombs[j]);
                                bombs[j].setAssigned(true);
                                bombs[j].setActive(true);
                                assigned = true;
                                invaders[i]->bomb->drawBomb(invaders[i]->getSprite().getPosition().x, invaders[i]->getSprite().getPosition().y, invaderAmmoPath);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    // to update the bombs of the invaders(their positions, whether they're active or not)
    void updateBombs()
    {
        for (int i = 0; i < noInvaders; i++)
        {
            if (invaders[i] != nullptr && invaders[i]->bomb != nullptr)
            {
                invaders[i]->bomb->moveBomb(0, 0.2);
                if (invaders[i]->bomb->getSprite().getPosition().y >= 700)
                {
                    invaders[i]->bomb->setActive(false);
                    invaders[i]->bomb->setAssigned(false);
                    invaders[i]->setBombActive(false);
                }
            }
        }
    }
    // to detect if the player has collided with an addon
    bool detectAddonAcquired()
    {
        for (int i = 0; i < noAddons; i++)
        {

            if (addons[i] != nullptr && addons[i]->getSprite().getPosition().x >= p->getSprite().getGlobalBounds().left &&
                addons[i]->getSprite().getPosition().x <= p->getSprite().getGlobalBounds().left + p->getSprite().getGlobalBounds().width &&
                addons[i]->getSprite().getPosition().y >= p->getSprite().getGlobalBounds().top &&
                addons[i]->getSprite().getPosition().y <= p->getSprite().getGlobalBounds().top + p->getSprite().getGlobalBounds().height)
            {
                p->setAddon(addons[i]);
                addons[i]->setActive(false);
                addons[i]->resetPosition(rand() % 700 + 30, 0);
                return true;
            }
        }
        return false;
    }
    // to genrerate an addon based on their turn of generation.
    // turn is included so that all addons get a chance to be generated, otherwise,
    // only one type of addon might be generated infintely
    void generateAddon(int turn)
    {

        if (addons[turn] != nullptr && !addons[turn]->getActive()) // if the addon is not already on screen
        {
            addons[turn]->resetPosition(rand() % 700 + 30, 60);
            addons[turn]->setActive(true);
        }
    }
    // to call the main screen function of the menu class
    void mainScreen()
    {
        music.play();
        menu.display_mainScreen();
        menu.display_mainMenu();
        start_game();
    }
    // to restart the game based on user input
    void restart_game()
    {
        if(p->addon!=nullptr)
        p->addon->setActive(false);
        for (int i = 0; i < noAddons; i++)
            if (addons[i] != nullptr)
            {
                addons[i]->setActive(false);
            }
        for (int i = 0; i < noInvaders; i++)
        {
            if (invaders[i] != nullptr)
                invaders[i]->setActive(false);
        }
        for (int i = 0; i < noBombs; i++)
        {
                bombs[i].setActive(false);
        }
        if (monster != nullptr)
            monster->setActive(false);
        if (dragon != nullptr)
            dragon->setActive(false);

        p->resetPlayer(noLives);
        start_game();
    }
    // to update the scores and sort the scores if the game is over
    void gameOver()
    {
        // cout<<"Hello"<<endl;
        writeScore();
        sortScore();
        if (menu.display_gameOver())
        {
            restart_game();
        }
    }
    // main game loop
    void start_game()
    {
        
        
        level = 1, phase = 1;   // deciding levels initally
        p->resetPlayer(noLives);// resetting the lives of the player
        decideLevel();          // deciding the starting level
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock, bomb, monsterClock, dragonClock, creatureClock, addonClock, specialAddonClock, shieldClock;
        clock.restart();
        bomb.restart();
        monsterClock.restart();
        dragonClock.restart();
        creatureClock.restart();
        addonClock.restart();
        specialAddonClock.restart();
        shieldClock.restart();
        bool isMonsterActive = false, isDragonActive = false, invadersPaused = false, specialAddon = false, addonsPaused = false, shieldActive = false;

        int creatureTurn = 0, addonTurn = 0;                   /// creatureTurn will decide which enemy(monster or dragon)
        float timer = 0, creatureAppearTime = rand() % 5 + 15, // generate a random time for the creatures(dragon/monster) to appear
            addonDropTime = rand() % 10,                       // to generate a random time for an addon to appear
            specialAddonTime = 0, shieldTime = 0;
        while (window.isOpen())
        {
            
            float time = clock.getElapsedTime().asSeconds();
            float currentBombTime = bomb.getElapsedTime().asSeconds();
            float creatureCurrentTime = creatureClock.getElapsedTime().asSeconds();
            float currentAddonTime = addonClock.getElapsedTime().asSeconds();
            

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // close the game
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                int check = menu.pauseMenu();
                if (check == 0) // check==0 means that the player has restarted the game
                {
                    
                    clock.restart();
                    bomb.restart();
                    monsterClock.restart();
                    dragonClock.restart();
                    creatureClock.restart();
                    specialAddonClock.restart();
                    shieldClock.restart();
                    window.close();
                    restart_game();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))                                            // If left key is pressed
                p->move("l");                                                                      // Player will move to left
            if (Keyboard::isKeyPressed(Keyboard::Right))                                           // If right key is pressed
                p->move("r");                                                                      // player will move to right
            if (Keyboard::isKeyPressed(Keyboard::Up))                                              // If up key is pressed
                p->move("u");                                                                      // playet will move upwards
            if (Keyboard::isKeyPressed(Keyboard::Down))                                            // If down key is pressed
                p->move("d");                                                                      // player will move downwards
            if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))    // If up and left key is pressed
                p->move("ld");                                                                     // player will move left diagonally
            if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))   // If up and right key is pressed
                p->move("rd");                                                                     // player will move right diagonally
            if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Down))  // If down and left key is pressed
                p->move("bld");                                                                    // player will move bottom left diagonally
            if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Down)) // If down and left key is pressed
                p->move("brd");                                                                    // player will move bottom right diagonally

            ////////////////////////////////////////////////
            /////        Call your functions here      ////
            //////////////////////////////////////////////
            // if the addon time elapsed is greater than the randomly generated addon drop time then generate and addon
            if (currentAddonTime >= addonDropTime)
            {
                generateAddon(addonTurn);
                addonClock.restart();
                currentAddonTime = 0;
                if (addonTurn >= noAddons - 1)
                    addonTurn = 0;
                else
                    addonTurn++;
                addonDropTime = rand() % 10;
            }
            if (detectAddonAcquired())
            {
                // deciding the change in functionality of the game based on which type of addon is acquired
                if (p->addon != nullptr && p->addon->getType() == "fire")
                {
                    p->setDestroyable(true);
                    specialAddon = true;
                    specialAddonClock.restart();
                    p->bullets->setNewTexture(fireAddonPath);
                }
                else if (p->addon != nullptr && p->addon->getType() == "powerup")
                {
                    specialAddon = true;
                    p->setDestroyable(false);
                    shieldActive=true;
                    specialAddonClock.restart();
                    p->bullets->setNewTexture(powerupAddonPath);
                }
                else if (p->addon != nullptr && p->addon->getType() == "lives")
                {
                    p->setDestroyable(true);
                    p->addon = nullptr;
                    p->setLives(1);
                }
                else if (p->addon != nullptr && p->addon->getType() == "danger")
                {
                    p->setDestroyable(true);
                    p->setLives(-1);
                    p->addon = nullptr;
                }
            }
            // special addons are fire and power up. which will last for five seconds thus have special functionality
            if (specialAddon)
            {
                specialAddonTime = specialAddonClock.getElapsedTime().asSeconds(); // specialAddOnTime stores the current time that the addon is active
                if (specialAddonTime >= 5)
                {
                    if (p->addon != nullptr && p->addon->getType() == "powerup")
                        p->setDestroyable(true);
                    specialAddonClock.restart();
                    specialAddon = false;
                    p->bullets->setNewTexture(originalBulletPath);

                    p->addon = nullptr;
                }
            }
            // firing bullet if the time elapsed is greater than the current time set for bullet fire
            if (time >= bulletTime)
            {
                p->fireBullet();
                fireBulletSound.play();
                clock.restart();
            }
            // detecting if the player shield is active
            if (shieldActive)
            {
                if (!p->getShield()) // if the shield is not already active
                {
                    shieldClock.restart();
                    p->setShield(true);
                    shieldTime = 0;
                    p->setDestroyable(false);
                }
                shieldTime = shieldClock.getElapsedTime().asSeconds();

                if (shieldTime > 5) // is elapsed time is greater than 5, set the shield to inactive
                {
                    shieldActive = false;
                    p->setShield(false);
                    p->setDestroyable(true);
                    shieldClock.restart();
                    shieldTime = 0;
                }
                else // otherwise move the shield along with the sprite
                    p->setShieldPosition();
            }
            // if the current bomb time exceeds the maximum interval of drop
            if (currentBombTime >= maxcurrentBombTime)
            {
                bomb.restart();
            }
            // if both are inactive, continue with the invaders
            if (!isDragonActive && !isMonsterActive)
            {
                invadersPaused = false;
            }
            // if the current time elapsed is greater than the random time set to appear for the creature
            if (creatureCurrentTime > creatureAppearTime && !isMonsterActive && !isDragonActive)
            {
                //creature turns are assigned so that there is an even distribution of the 
                //creatures(dragon and monster). otherwise, only one type of creature could 
                //be generated infintely 
                if (creatureTurn == 0)
                {
                    creatureTurn = 1;
                    isMonsterActive = true;
                    monster->bomb->setActive(true);
                    invadersPaused = true;
                    isDragonActive = false;
                    monster->setDodgeMonster(true);
                }
                else if (creatureTurn == 1)
                {
                    creatureTurn = 0;
                    isDragonActive = true;
                    isMonsterActive = false;
                    invadersPaused = true;
                }
                creatureCurrentTime = 0;
                creatureAppearTime = rand() % 5 + 15;
                creatureClock.restart();
                addonsPaused = true;
            }

            if (isDragonActive || isMonsterActive) // only check if either of them are active
            {
                //if the elapsed time for which the creature is on screen is greater than the
                //maximum time set for it to be on screen, set the creature to inactive
                if (creatureCurrentTime >= maxMonsterTime && isMonsterActive)
                {
                    isMonsterActive = false;
                    creatureCurrentTime = 0;
                    invadersPaused = false;
                    addonsPaused = false;
                    if (monster->getDodgeMonster())
                    {
                        calculateScore(monster->getKillScore());
                    }
                    // cout << p->getScore() << endl;
                }
                else if (creatureCurrentTime >= maxDragonTime && isDragonActive)
                {
                    isDragonActive = false;
                    creatureCurrentTime = 0;
                    invadersPaused = false;
                    addonsPaused = false;
                }
            }
            //if the monster is currently acitve, move the monster and along with it, its bomb
            if (isMonsterActive)
            {
                monster->moveEnemy();
                monster->bomb->drawBomb(monster->getSprite().getPosition().x + 45, monster->getSprite().getPosition().y + 5, monsterAmmoPath);

                if ((int)creatureCurrentTime % 2 == 0)  //decides if the bomb has been on screen for two seconds 
                    monster->bomb->setActive(false);
                else
                    monster->bomb->setActive(true);
                if (p->getDestroyable())   //this checks if the player is destroyable or not. if it is not, does not detect collision
                    if (monsterCollision())
                    {
                        shieldActive = true;   //if the player has collided with the monster bomb or the monster, set its shield and restart its position 
                        p->restart();
                    }
            }
//invaders could be paused based on whether a monster or creature is on screen. does not check collisions or updates the bombs if true 
            if (!invadersPaused)
            {
                assignBombs(currentBombTime);
                updateBombs();
                // detecting bullet collisoin
                detectBulletCollision();
                //--------------------//
                // player collision check
                if (p->addon == nullptr)
                {
                    if (p->getDestroyable())
                    {
                        // detecting bomb collision
                        if (detectPlayerCollision() || detectBombCollision())
                        {
                            shieldActive = true;
                            p->setLives(-1);
                            p->restart();
                        }
                    }
                }
            }

            p->updateBullets(); // this function updates the bullets, whether bullet is active or not

            // checking if current phase is complete.
            
            if (checkPhase())
            {
                window.close();

                if (menu.display_gameComplete())  //will return true if the player has selected the restart game option 
                {
                    restart_game();
                }
            }

            if (checkLives())
            {
                window.close();
                currentBombTime=0;
                gameOver();
            }

            //==========------------Drawing elements-----------=============//
            window.clear(Color::Black); // clears the screen
            window.draw(background);    // setting background
            window.draw(p->sprite);
            if (p->getShield())
                window.draw(p->shield);

            if (!addonsPaused)
                for (int i = 0; i < noAddons; i++)
                {
                    if (addons[i] != nullptr && addons[i]->getActive())
                    {
                        addons[i]->moveAddon();
                        if (addons[i]->getType() == "danger" && addons[i]->isDodged())
                        {
                            calculateScore(5);
                            addons[i]->setDodged(false);
                            // cout << p->getScore() << endl;
                        }
                        window.draw(addons[i]->getSprite());
                    }
                }

            if (dragon != nullptr && isDragonActive)
            {

                if (p->getSprite().getPosition().x > 320 && p->getSprite().getPosition().x < 410)
                {
                    dragon->bomb[0].setActive(true);
                    dragon->bomb[2].setActive(false);
                    dragon->bomb[1].setActive(false);
                    window.draw(dragon->bomb[0].getSprite());
                }
                else if (p->getSprite().getPosition().x > 0 && p->getSprite().getPosition().x < 300)
                {
                    dragon->bomb[1].setActive(true);
                    dragon->bomb[0].setActive(false);
                    dragon->bomb[2].setActive(false);
                    window.draw(dragon->bomb[1].getSprite());
                }

                else if (p->getSprite().getPosition().x > 420 && p->getSprite().getPosition().x < 700)
                {
                    dragon->bomb[0].setActive(false);
                    dragon->bomb[1].setActive(false);
                    dragon->bomb[2].setActive(true);
                    window.draw(dragon->bomb[2].getSprite());
                }
                if (p->getDestroyable())
                    detectDragonCollision();
                window.draw(dragon->getSprite());
            }
            if (isMonsterActive)
            {
                if (monster->bomb != nullptr && monster->bomb->getActive())
                {
                    while (!(monster->bomb->getSprite().getPosition().y >= 740))
                    {
                        monster->bomb->moveBomb(0, 2);
                        window.draw(monster->bomb->getSprite());
                    }
                }
                window.draw(monster->getSprite());
            }

            if (!invadersPaused)
            {
                for (int i = 0; i < noInvaders; i++)
                {
                    if (invaders[i] != nullptr && invaders[i]->bomb != nullptr)
                    {
                        window.draw(invaders[i]->bomb->getSprite());
                    }
                }

                for (int i = 0; i < noInvaders; i++) // drawing the invaders
                    if (invaders[i]->getActive() && invaders[i] != nullptr)
                        window.draw(invaders[i]->getSprite());
            }
            for (int i = 0; i < p->getNumBullets(); i++) // drawing the active bullets
            {
                if (p->bullets[i].isActive())
                    window.draw(p->bullets[i].sprite);
            }

            ostringstream userscore, score1, score2, score3, livesLeft; // score1, score2, score3 display the high scores in descending order
            userscore << "SCORE: " << p->getScore();

            score1 << "1. " << scores[0];
            score2 << "2. " << scores[1];
            score3 << "3. " << scores[2];
            livesLeft << "LIVES: " << p->getLives();
            currentScore.setString(userscore.str());
            highscore1.setString(score1.str());
            highscore2.setString(score2.str());
            highscore3.setString(score3.str());
            lives.setString(livesLeft.str());

            window.draw(currentScore);  //drawing the current score
            window.draw(highscore1); // drawing highscores and the current score on screen
            window.draw(highscore2);
            window.draw(highscore3);
            window.draw(lives);
            window.display(); // Displying all the sprites
        }
    }
};
