#include "Game.h"

//Initialize 
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1600, 1000), "Game 3", sf::Style::Fullscreen | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 5.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Images/bullet.png");

}

void Game::initGUI()
{
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
    
    //Init bulletVector
	this->bulletVector.setPosition(700.f, 25.f);
	this->bulletVector.setFont(this->font);
	this->bulletVector.setCharacterSize(52);
	this->bulletVector.setFillColor(sf::Color::White);

    //Init getHp
	this->getHp.setPosition(700.f, 185.f);
	this->getHp.setFont(this->font);
	this->getHp.setCharacterSize(52);
	this->getHp.setFillColor(sf::Color::White);

    //Init mousePos
	this->mousePos.setPosition(700.f, 105.f);
	this->mousePos.setFont(this->font);
	this->mousePos.setCharacterSize(52);
	this->mousePos.setFillColor(sf::Color::White);

    //Init myPointsText
	this->myPointsText.setPosition(0.f, 50.f);
	this->myPointsText.setFont(this->font);
	this->myPointsText.setCharacterSize(52);
	this->myPointsText.setFillColor(sf::Color::White);

    //Hp bar
	this->hpBarFront.setSize(sf::Vector2f(300.f, 25.f));
	this->hpBarFront.setFillColor(sf::Color::Red);
	this->hpBarFront.setPosition(sf::Vector2f(20.f, 20.f));

    this->hpBarBack = this->hpBarFront;
    this->hpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
    this->hpBarBack.setOutlineThickness(3.f);
    this->hpBarBack.setOutlineColor(sf::Color::White);

}

void Game::initBackground()
{
    if(!this->worldBackgroundTex.loadFromFile("Images/Background.png"))
    {
        std::cout << "Couldn't load background" << std::endl;
    }

    this->worldBackground.setTexture(this->worldBackgroundTex);
    // this->worldBackground.setPosition(1000, 1000);
    this->worldBackground.scale(12.f, 12.f);
}

//Const Dest
Game::Game()
{
    this->initWindow();
    this->initBackground();
    this->initPlayer();
    this->initEnemies();
    this->initTextures();
    this->initGUI();
}

Game::~Game()
{
    delete this->window;
    delete this->player;

    //Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

    //Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto *i : this->enemies)
	{
		delete i;
	}

}

int Game::getPoints()
{
    return this->points;
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::updateInput()
{
    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);
    
    //Shoot
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->bullets.push_back(
            new Bullet(
            this->textures["BULLET"], 
			this->player->getPos().x + this->player->getBounds().width/2.f, 
			this->player->getPos().y, 
			0.f, 
			-1.f, 
			10.f,
            1.f
            )
        );
    }
}

void Game::updateEnemies()
{
    //Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

    //Update
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
        
		++counter;
	}
}

void Game::updateBullets()
{

    for (auto i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->update();

        //Bullet culling (top of screen)
        if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0.f)
        {
            delete this->bullets[i];
            this->bullets.erase(this->bullets.begin() + i);
        }
    }

}

void Game::updateBounds()
{
    //Left bound
    if(this->player->getBounds().left < 0.f)
        this->player->setPosition(0.f, this->player->getBounds().top);
    //Right bound
    if(this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    //Top bound
    if(this->player->getBounds().top < 0.f)
        this->player->setPosition(this->player->getBounds().left, 0.f);
    //Bottom bound
    if(this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
}

void Game::updateCombat()
{   
    //Bullet enemy collision
    for (size_t i = 0; i < this->enemies.size(); i++)
    {   
        //Bullet enemy collision
        bool enemyDeleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemyDeleted == false; k++)
        {
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                this->points += this->enemies[i]->getPoints();
                // std::cout << this->enemies[i]->getPoints() << std::endl;
            }
        }
        //Enemy player collision
        if(this->enemies[i]->getBounds().intersects(this->player->getBounds()))
        {
            this->player->takeDamage(10);

            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::updateGUI()
{
    //bulletVector
    std::stringstream ss1;
	ss1 << "bulletVector: " << this->bullets.size();
	this->bulletVector.setString(ss1.str());

    //getHp
    std::stringstream ss2;
	ss2 << "Health: " << this->player->getHp();
	this->getHp.setString(ss2.str());

    //mousePos
    std::stringstream ss3;
	ss3 << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " , " << sf::Mouse::getPosition(*this->window).y;
	this->mousePos.setString(ss3.str());

    //myPointsText
    std::stringstream ss4;
	ss4 << "Points: " << this->getPoints();
	this->myPointsText.setString(ss4.str());

    //Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->hpBarFront.setSize(sf::Vector2f(300.f * hpPercent, this->hpBarFront.getSize().y));

}

void Game::update()
{
    this->updateInput();
    this->player->update();
    this->updateEnemies();
    this->updateBullets();
    this->updateGUI();
    this->updateBounds();
    this->updateCombat();
}

void Game::renderGUI()
{
    this->window->draw(this->bulletVector);
    this->window->draw(this->getHp);
    this->window->draw(this->mousePos);
    this->window->draw(this->myPointsText);
    this->window->draw(this->hpBarBack);
	this->window->draw(this->hpBarFront);

}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->pollEvents();

		this->update();

		this->render();
	}
}


void Game::render()
{
    this->window->clear();

    this->renderWorld();

    //Draw game
    this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

    for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

    this->renderGUI();

    this->window->display();
}
