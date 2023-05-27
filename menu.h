#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;
#ifndef MENU_H
#define MENU_H
class Menu
{
public:
    string mainScreenPath = "img/screens/mainscreen.png",
           mainMenuPath = "img/screens/mainMenu.png",
           instructionScreenPath = "img/screens/instructions.png",
           pausePath = "img/screens/pause.png",
           gameCompletePath="img/screens/gameComplete.png",
           gameOverPath="img/screens/gameOver.png";
    Texture mainScreenTex, mainMenuTex, instructionsTex, pauseTex, gameCompleteTex, gameOverTex;
    Sprite mainScreen, mainMenu, instructions, pause, gameComplete, gameOver;
    Menu()
    {
        mainScreenTex.loadFromFile(mainScreenPath);
        mainScreen.setTexture(mainScreenTex);
        mainScreen.setScale(0.71, 0.73);

        mainMenuTex.loadFromFile(mainMenuPath);
        mainMenu.setTexture(mainMenuTex);
        mainMenu.setScale(0.71, 0.73);

        instructionsTex.loadFromFile(instructionScreenPath);
        instructions.setTexture(instructionsTex);
        instructions.setScale(0.71, 0.73);

        pauseTex.loadFromFile(pausePath);
        pause.setTexture(pauseTex);
        pause.setScale(0.71, 0.73);

        gameCompleteTex.loadFromFile(gameCompletePath);
        gameComplete.setTexture(gameCompleteTex);
        gameComplete.setScale(0.71, 0.73);


        gameOverTex.loadFromFile(gameOverPath);
        gameOver.setTexture(gameOverTex);
        gameOver.setScale(0.71, 0.73);
    }

    int display_mainScreen()
    {

        RenderWindow window(VideoMode(780, 780), "Main Screen");
        while (window.isOpen())
        {
            Event e;
            window.draw(mainScreen);
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                    
                if (Keyboard::isKeyPressed(Keyboard::Space))
                {
                    return 1;
                }
            }
            window.display();
        }
        return 0;

    }
    int display_mainMenu()
    {
        RenderWindow window(VideoMode(780, 780), "Main Menu");
        while (window.isOpen())
        {
            Event e;
            window.draw(mainMenu);
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Num1))
                {
                    return 1;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num4))
                {
                    exit(0);
                }
                if (Keyboard::isKeyPressed(Keyboard::Num2))
                {
                    bool check = true;
                    window.draw(instructions);
                    while (check)
                    {
                        window.display();
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                            check = false;
                    }
                }
            }
            window.display();
        }
        return 0;
    }
    int pauseMenu()
    {
        RenderWindow window(VideoMode(780, 780), "Pause Screen");
        bool pauseCheck = true;
        window.draw(pause);
        window.display();
        while (pauseCheck)
        {
            Event e;

            while (window.pollEvent(e))
            {

                if (e.type == Event::Closed)
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Num1))
                {
                    return 1;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num2))
                {
                    return 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num3))
                {
                    bool check = true;
                    window.draw(instructions);
                    while (check)
                    {
                        window.display();
                        if (Keyboard::isKeyPressed(Keyboard::Num0))
                        {
                            window.close();
                            return 1;
                    
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Num4))
                {
                    exit(0);
                }
            }
        }

        window.draw(pause);
        window.display();

        return 0;
    }
        int display_gameComplete()
    {
        RenderWindow window(VideoMode(780, 780), "Game Over Screen");

        while (window.isOpen())
        {
            Event e;
            window.draw(gameComplete);
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                    
                if (Keyboard::isKeyPressed(Keyboard::Num1))
                {
                    return 1;
                }
                if(Keyboard::isKeyPressed(Keyboard::Num2))
                {
                    bool check = true;
                    window.draw(instructions);
                    while (check)
                    {
                        window.display();
                        if (Keyboard::isKeyPressed(Keyboard::Num0))
                        {
                            check=false;
                    
                        }
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Num3))
                {
                    exit(0);
                }
            }
            window.display();
        }
        return 0;
    }
    int display_gameOver()
    {
        RenderWindow window(VideoMode(780, 780), "Game Over Screen");

        while (window.isOpen())
        {
            Event e;
            window.draw(gameOver);
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                    
                if (Keyboard::isKeyPressed(Keyboard::Num1))
                {
                    return 1;
                }
                if(Keyboard::isKeyPressed(Keyboard::Num2))
                {
                    bool check = true;
                    window.draw(instructions);
                    while (check)
                    {
                        window.display();
                        if (Keyboard::isKeyPressed(Keyboard::Num0))
                        {
                            check=false;
                    
                        }
                    }
                }
                if(Keyboard::isKeyPressed(Keyboard::Num3))
                {
                    exit(0);
                }
            }
            window.display();
        }
        return 0;
    }
};
#endif
