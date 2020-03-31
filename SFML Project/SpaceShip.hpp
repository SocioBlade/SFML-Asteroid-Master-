#pragma once
#include <math.h>
#include "Asteroids.hpp"
#include "Entity.h"
#include "Const.hpp"

#include <SFML\Graphics.hpp>

class SpaceShip : public Entity
{
public:
	SpaceShip();
	~SpaceShip();

	void shot();
	void update(float frameTime);

	sf::Vector2f getPlayerCenter();
	float getPlayerAngle();
	bool getIsAlive();
	void setLife();
	void setDrawLife();

	template<class A>
	bool asteroidColCheck(A&a);

private:
	int hp;
	int speed;

	float posX;
	float posY;
	float dirX;
	float dirY;
	float angle;
	bool thrust;
	bool isAlive;
	bool drawLife;

	sf::Vector2f playerCenter;
	sf::Vector2f playerDirection;
};

template<class A>
inline bool SpaceShip::asteroidColCheck(A & a)
{
	if (this->eShape.getGlobalBounds().intersects(a.getAsteroidShape().getGlobalBounds())) {
		this->drawLife = true;
	}
	return drawLife;
}