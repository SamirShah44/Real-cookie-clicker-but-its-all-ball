
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>

class Game
{
    private:
    //Variables
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    //Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Game Objects
    sf::CircleShape enemy;
    std::vector<sf::CircleShape> enemies;

    //Resources
    sf::Font font; 

    //Text
    sf::Text uiText;

    //Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpwanTimer;
    float enemySpwanTimerMax;
    int maxEnemies;
    bool mouseHeld;

    // Private functions
    void  initVariable();
    void initWindow();
    void initEnemies();
    void initFonts();
    void initText();
    void updateMousePositions();


    public:
        Game();

        virtual ~Game();

        //Accessors
        const bool running() const;
        const bool getEndGame() const;

        //FUnctions
        void spwanEnemies();

        void updatePollEvent();
        void updateEnemies();
        void updateText();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render();

};

#endif // GAME_H
