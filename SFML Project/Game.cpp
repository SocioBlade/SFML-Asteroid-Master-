#include "Game.h"

Game::Game()
{
	srand(unsigned int(time(NULL)));
	this->placeAsteroid();
	this->placeDeadBullets();
	this->amtFiredBullets = 0;
	this->fireTimer = 0.f;
	this->fireTimeMax = 0.2f;
	this->deathTimer = 0.f;
	this->deathTimerMax = 0.5;
}


Game::~Game()
{
}

void Game::placeAsteroid()
{
	for (int i = 0; i < 20; i++) {
		asteroid[i].setPosRotSpd(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT,
			static_cast<float>(rand() % 360), static_cast<float>(rand() % 360),
			static_cast<float>(rand() % 360), static_cast<float>(rand() % 2 + 1));
	}
}

void Game::placeDeadBullets()
{
	for (int i = 0; i < BULLET_CAP; i++) {
		projectile[i].setBulletPos(640.f, 360.f);
	}
}

void Game::gameUpdate(float frameTime)
{
	if (playerShip.getIsAlive()) {
		//Collision between bullet and asteroid
		for (int i = 0; i < BULLET_CAP; i++) {
			for (int j = 0; j < ASTEROID_ONE_CAP; j++) {
				if (this->projectile[i].getState() == 1) {
					if (this->asteroid[j].bulletColCheck(this->projectile[i])) {
						this->projectile[i].bulletHasHit();
						this->gameUI.setScore();
						this->asteroid[j].setGivePoint();
					}
				}
			}
		}

		for (int i = 0; i < ASTEROID_ONE_CAP; i++) {
			if (this->playerShip.asteroidColCheck(this->asteroid[i])) {
				this->playerShip.setLife();
				this->gameUI.setLife();
				this->playerShip.setDrawLife();
			}
		}
	
		//Update Bullets
		for (int i = 0; i < BULLET_CAP; i++)
			this->projectile[i].update(frameTime, playerShip);

		//Update Asteroids
		for (int i = 0; i < ASTEROID_ONE_CAP; i++)
			this->asteroid[i].update(frameTime);
	
		//Update UI
		this->gameUI.update();

		//Update player
		this->playerShip.update(frameTime);
			



		this->fireTimer += frameTime;
		if (this->fireTimer >= this->fireTimeMax) {
			//KeyCheck
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				this->fireTimer = 0;
				amtFiredBullets++;
				for (int i = 0; i < amtFiredBullets; i++)
					projectile[i].setMoving();
			}
		}
		if (amtFiredBullets >= BULLET_CAP)
			amtFiredBullets = 0;
	}
	if (!playerShip.getIsAlive())
		gameOverState();
}

void Game::gameOverState()
{
	gameUI.displayFinalScore();
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Draw pojectiles
	for (int i = 0; i < BULLET_CAP; i++) {
		target.draw(this->projectile[i], states);
	}

	//Draw player
	target.draw(this->playerShip, states);

	//Draw asteroids
	for (int i = 0; i < ASTEROID_ONE_CAP; i++)
		target.draw(this->asteroid[i], states);

	//Draw UI
	target.draw(this->gameUI, states);
}