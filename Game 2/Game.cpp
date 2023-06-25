#include "Game.h"


void Game::initVariable()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 10;
    this->points = 0;
}

void Game::initWindow()
{
    // this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Fullscreen | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/ARCADECLASSIC.TTF"))
    {
        std::cout << "Could not load fonts" << "\n";
    }
}

void Game::initText()
{
    //Gui init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(56);

    //End game text init
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setStyle(sf::Text::Bold);
    this->endGameText.setPosition(400.f, 300.f);
    this->endGameText.setString("YOU DIED");
  
}

// Constructors & Destructors
Game::Game()
{
    this->initVariable();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::getEndGame() const
{
    return this->endGame;
}


// Functions
const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch (this->sfmlEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        
        case sf::Event::KeyPressed:
            if(this->sfmlEvent.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}

const int Game::randBallType() const
{
    int type = BallTypes::DEFAULT;
    int randValue = rand() % 100 + 1;

    if (randValue > 50 && randValue <= 75)
        type = BallTypes::DAMAGING;
    else if (randValue > 75 && randValue <= 100)
        type = BallTypes::HEALING;

    return type;
}

void Game::spawnBalls()
{
    //Timer
    if (this->spawnTimer < this->spawnTimerMax)
    {
        this->spawnTimer += 1.f;
    }
    else
    {
        if (this->balls.size() < this->maxBalls)
        {
            this->balls.push_back(Balls(*this->window, this->randBallType()));

            this->spawnTimer = 0.f;
        }
    }
}

void Game::updatePlayer()
{
    this->player.update(this->window);

    if (this->player.getSize().x <= 0 && this->player.getSize().x <= 0)
        this->endGame = true;

}

void Game::updateCollision()
{
    //Check the collision

    for (size_t i = 0; i < this->balls.size(); i++)
    {
        if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
        {
            switch (this->balls[i].getType())
            {
            case BallTypes::DEFAULT:
                this->points++;
                break;
            case BallTypes::DAMAGING:
                this->player.gainSize(-20.f);
                break;
            case BallTypes::HEALING:
                this->points++;
                this->player.gainSize(20.f);
                break;
            }

            //Add points
            this->points++;

            //Remove the ball
            this->balls.erase(this->balls.begin() + i);
        }
    }

}

void Game::updateGui()
{
    std::stringstream ss;
    
    ss << "     " << this->points << "     Points" << "\n"
        << "     " << this->player.getSize().x << "     Health" << "\n";

    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();

    if(this->player.getSize().x <= 0)
        this->endGame = true;

    this->updatePlayer();
    this->randBallType();
    this->spawnBalls();
    this->updateCollision();
    this->updateGui();

    //Output testing

    /*std::cout << rand() % this->window->getSize().x << std::endl;*/

    //sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
    //std::cout << "Mouse X: " << mousePosition.x << ", Mouse Y: " << mousePosition.y << std::endl;
}

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear();

    //Draw game
    this->player.render(this->window);

    for (auto i : this->balls)
    {
        i.render(*this->window);
    }

    //Render gui
    this->renderGui(this->window);


    //Render end text
    if (this->endGame)
    {
        this->window->draw(this->endGameText);
    }

    this->window->display();
}
