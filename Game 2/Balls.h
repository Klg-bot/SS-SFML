#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NROTYPES};

class Balls
{
private:
	sf::CircleShape shape;
	int type;

	void initShape(const sf::RenderWindow& window);

public:	
	//Constructor Destructor
	Balls(const sf::RenderWindow& window, int type);
	virtual ~Balls();

	//Accesors
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update();
	void render(sf::RenderTarget & target);

};

