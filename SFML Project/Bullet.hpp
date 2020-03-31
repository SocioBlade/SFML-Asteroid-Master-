#pragma once
#include <math.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Const.hpp"
#include "SpaceShip.hpp"
#include "Entity.h"


class Bullet : public Entity, sf::Transformable {
public:
	Bullet();
	~Bullet();

	int getState() const;

	void setBulletPos(float posX, float posY);
	void setBulletDir();
	void setDistance(float frameTime);
	void setAngle(float angle);
	void setMoving();
	void isFiring();
	void bulletMove(sf::Vector2f playerPos, float angle, float frameTime);
	void bulletBoundCheck();
	void bulletHasHit();
	void update(float frameTime, class SpaceShip playerRef);
	void bulletIdleUpdate();
	void bulletShootingUpdate(class SpaceShip playerRef, float frameTime);
	sf::RectangleShape getBulletShape() const;


private:
	static const float speed;
	sf::Vector2f bulletPos;
	sf::Vector2f bulletDir;
	sf::Vector2f distance;
	float angle;
	bool isMoving;
	bool isLoaded;
	bool isStored;
	bool isHit;
	int bulletState;
	float posX;
	float posY;
};
