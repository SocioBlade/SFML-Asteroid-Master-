#pragma once
#include <SFML\Graphics.hpp>
#include "Const.hpp"
#include "Bullet.hpp"
#include "Entity.h"

class Asteroids : public Entity
{
public:
	Asteroids();
	~Asteroids();

	void update(float frameTime);
	void setPosRotSpd(int posX, int posY, float dirX, float dirY, float angle,
		float maxSpeed);
	sf::RectangleShape getAsteroidShape();
	void bBoxDraw(sf::RenderWindow &window);
	bool getGivePoint();
	void setGivePoint();
	template <class B>
	bool bulletColCheck(B& b);

private:
	//int sprIndex;
	int rotateCheck,
		imageIndex;

	float posX,
		posY,
		dirX,
		dirY,
		angle,
		maxSpeed,
		timer,
		timerMax,
		spawnTimer;

	bool isHit,
		isSpawning,
		givePoint;
};

//Collision check with bullet, if bullet hits, move this Asteroid
template<class B>
inline bool Asteroids::bulletColCheck(B & b)
{
	if (this->eShape.getGlobalBounds().intersects(b.getBulletShape().getGlobalBounds())) {
		this->isHit = true;
		this->givePoint = true;
		this->eShape.setPosition(-64, WINDOW_HEIGHT);
		this->eSprite.setPosition(this->eShape.getPosition());
		maxSpeed = 0;
	}
	return this->givePoint;
}