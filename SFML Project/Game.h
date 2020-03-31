#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string>


#include "SpaceShip.hpp"
#include "Asteroids.hpp"
#include "Bullet.hpp"
#include "FontHandler.h"

class Game : public sf::Drawable
{
public:
	Game();
	~Game();

	void placeAsteroid();
	void placeDeadBullets();

	void gameUpdate(float frameTime);
	void gameOverState();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	FontHandler gameUI;
	Bullet projectile[BULLET_CAP];
	SpaceShip playerShip;
	Asteroids asteroid[20];
	int amtFiredBullets;
	float fireTimer;
	float fireTimeMax;
	float deathTimer;
	float deathTimerMax;
};

