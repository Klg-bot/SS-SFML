#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 1000;
}

void Game::initWindows()
{
    this->videoMode.height = 1200;
    this->videoMode.width = 1900;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Resize | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
}

void Game::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Fonts.ttf"))
    {
        std::cout << "Failed to load fonts!" << std::endl;
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");

}

// Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindows();
    this->initEnemies();
    this->initText();
    this->initFonts();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

// Functions
void Game::spawnEnemy()
{

    //Random spawn position
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    //Randomise enemy type
    this->enemyType = rand() % 5;

    switch (this->enemyType)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    //Spawn enemy 
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
    //game polling 
    while(this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        
        case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::updateMousePositions()
{
    /*
        @return void

        Updates the mouse positions:
        - mouse position relative to window (Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Health: " << this->health;

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    /*
        @return void

        Updates enemy spawn timer and spawns enemies
        when the total amount of enemies is smaller than max.
        Moves enemies downards
        Removes the enemies at the edge of the screen. //TODO
    */


    //Updating timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn enemy and reset timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //Moving and updating enemies
    for(int i = 0; i < this->enemies.size(); i ++)
    {
        //Moving enemies downwards
        this->enemies[i].move(0.f, 5.f); 

        //Delete if past screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            
            this->health -= 1;
            // std::cout << "Health: " << this->health << std::endl;
        }
    }

    //Check if clicked upon
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if(this->mouseHeld == false)
            {
                this->mouseHeld = true;
                bool deleted = false;

                for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
                {
                    if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                    {
                        //Gain points
                        switch (this->enemyType)
                        {
                            case 0:
                                health += 30;
                                break;
                            case 1:
                                health += 25;
                                break;
                            case 2:
                                health += 20;
                                break;
                            case 3:
                                health += 15;
                                break;
                            case 4:
                                health += 10;
                                break;
                            default:
                                health += 20;
                                break;                            
                        }

                        //Delete enemy 
                        deleted = true;
                        this->enemies.erase(this->enemies.begin() + i);
                    }
                }
            }
        }

        else
        {
            this->mouseHeld = false;
        }

}

void Game::update()
{
    this->pollEvents();

    if(this->endGame == false)
    {
        this->updateMousePositions();

        this->updateEnemies();

        this->updateText();
    }

    //End game condition
    if(this->health <= 0)
    {
        this->endGame = true;
    }

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all the enemies
    for(auto &e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    /*  
        @returns void
        
        - clear old frames
        - renders objects
        - display frame in window    

        Renders the game objects
    */

    this->window->clear();

    //Draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
