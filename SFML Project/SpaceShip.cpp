#include "SpaceShip.hpp"

SpaceShip::SpaceShip()
	:Entity(32.f, 16.f, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f, 1.f, 1.f,
		32.f, 32.f, "../Resources/ship.png")
{
	this->hp = 100;
	this->posX = 640.f;
	this->posY = 320.f;
	this->dirX = 0;
	this->dirY = 0;
	this->angle = 0;
	this->isAlive = true;
}


SpaceShip::~SpaceShip()
{
}

void SpaceShip::shot()
{
	hp -= 1;

	if (hp == 0)
		isAlive = false;
}

//Player Movement
void SpaceShip::update(float frameTime)
{
	if (hp != 0) {
		//Keyboard input for movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			angle += 3.5f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			angle -= 3.5f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			thrust = true;
		else
			thrust = false;
	
		//If thrust is true, direction of player is calculated
		if (thrust == true)
		{
			dirX += cos(angle*DEGTORAD)*0.5f;
			dirY += sin(angle*DEGTORAD)*0.5f;
		}
		else
		{
			//Calculates the friction in space. Science accurate 
			dirX *= 0.995f;
			dirY *= 0.995f;
		}

		int maxSpeed = 6;
		float speed = sqrt(dirX*dirX + dirY*dirY);
		if (speed > maxSpeed)
		{
			dirX *= maxSpeed / speed;
			dirY *= maxSpeed / speed;
		}

		this->posX += dirX;
		this->posY += dirY;

		if (posX > WINDOW_WIDTH) posX = 0;
		if (posX < 0) posX = WINDOW_WIDTH;
		if (posY > WINDOW_HEIGHT) posY = 0;
		if (posY < 0) posY = WINDOW_HEIGHT;

		this->eShape.setPosition(posX, posY);
		this->eSprite.setPosition(this->eShape.getPosition());
		this->eShape.setRotation(this->angle);
		this->eSprite.setRotation(this->eShape.getRotation());
		playerCenter = this->eShape.getPosition();
	}
	if (hp <= 0) {
		eShape.setPosition(0, -64);
		eSprite.setPosition(eShape.getPosition());
		isAlive = false;
	}
}

sf::Vector2f SpaceShip::getPlayerCenter()
{
	return playerCenter;
}

float SpaceShip::getPlayerAngle()
{
	return angle;
}

bool SpaceShip::getIsAlive()
{
	return isAlive;
}

void SpaceShip::setLife()
{
	this->hp--;
}

void SpaceShip::setDrawLife()
{
	this->drawLife = false;
}