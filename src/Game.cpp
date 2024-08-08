#include <iostream>
#include "Game.h"
using namespace std;

// Private func
void Game::initVariable()
{
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->health = 50;
    this->enemySpwanTimerMax = 10.f;
    this->enemySpwanTimer = this->enemySpwanTimerMax;
    this->maxEnemies = 50;
    this->mouseHeld = false;
    this->endGame = false;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "My Game Window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(70);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setRadius(10.f);
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(4.f);
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("font/Dosis-Light.ttf"))
    {
        std::cout << "Failed font" << std::endl;
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(36);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("None");
}

void Game::updateMousePositions()
{
    // update mouse position relative to window
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

// Public functions
// Constructor
Game::Game()
{
    // ctor
    this->initVariable();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}
// Destructor
Game::~Game()
{
    // dtor
    delete this->window;
}

const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return endGame;
}

void Game::spwanEnemies()
{
    // TODo for spwan enemies
    /*
        Set random position
        set random color to fill it
        add enemy to the vector
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getRadius())),
        0.f // ALways at top not random//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y- this->enemy.getSize().y))
    );

    // Randomize enemy type
    int type = rand() % 5;
    switch (type)
    {
    case 0:
        this->enemy.setRadius(10.f);
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setRadius(15.f);
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setRadius(20.f);
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setRadius(25.f);
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setRadius(30.f);
        this->enemy.setFillColor(sf::Color::Green);
        break;

    default:
        this->enemy.setRadius(10.f);
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    this->enemies.push_back(this->enemy);
}

void Game::updatePollEvent()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}

void Game::updateEnemies()
{

    // Updating the timer for the enemies spwaning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpwanTimer >= this->enemySpwanTimerMax)
        {
            // spwan the enemies and reset the timer
            this->spwanEnemies();
            this->enemySpwanTimer = 0;
        }
        else
        {
            this->enemySpwanTimer += 1.f;
        }
    }
    // Move the enemies and update them
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
        this->enemies[i].move(0.f, 1.f);

        // If enemy has passed the bottom of screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            i--;
            this->health -= 1;
            cout << "Health :" << this->health << endl;
        }
    }

    // TODO :Remove the enemies at the edge of the screen

    // CHeck if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {



                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                    {this->points += 10.f;}
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue){
this->points += 7.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan){
this->points += 5.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Red ){
                   this->points += 3.f;

                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Green){
this->points += 1.f;
                    }
                    else{
this->points += 1.f;
                    }
                    cout << "Points :" << this->points << endl;
                     // Gain point
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    i--;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << endl
       << "Health: " << this->health;
    this->uiText.setString(ss.str());
}

void Game::update()
{
    this->updatePollEvent();

    if (!this->endGame)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    // End the game
    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget &target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget &target)
{
    // Rendering all enmies
    for (auto &e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    // Clear the screen
    this->window->clear();

    // THen draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);
    this->window->display();
}
