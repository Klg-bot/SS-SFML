#include "Game.h"

//Initialize 
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1600, 1000), "Game 3", sf::Style::Fullscreen | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
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
    
    //Init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(52);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
}

//Const Dest
Game::Game()
{
    this->initWindow();
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
			2.f
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
    std::vector<int> bulletsToDelete;

    for (auto i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i]->update();

        //Bullet culling (top of screen)
        if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0.f)
        {
            bulletsToDelete.push_back(i);
        }
    }

    for(auto i = bulletsToDelete.rbegin(); i != bulletsToDelete.rend(); ++i)
    {
        delete this->bullets[*i];
        this->bullets.erase(this->bullets.begin() + *i);
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
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        bool enemyDeleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemyDeleted = false; k++)
        {
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

                
            }
        }
        
    }
    
}

void Game::updateGUI()
{
    std::stringstream ss;

	ss << "Bullet-vector: " << this->bullets.size();;

	this->pointText.setString(ss.str());
}

void Game::update()
{
    this->updateInput();
    this->player->update();
    this->updateEnemies();
    this->updateBullets();
    this->updateGUI();
    this->updateBounds();
}

void Game::renderGUI()
{
    this->window->draw(this->pointText);
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
