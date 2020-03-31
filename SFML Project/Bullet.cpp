#include "Bullet.hpp"

const float Bullet::speed = 2000.f;

Bullet::Bullet()
	:Entity(4.f, 4.f, WINDOW_WIDTH + 16.f, WINDOW_HEIGHT, 1.f, 1.f, 4.f, 4.f, 
		"../Resources/spr_bullet_0.png")
{
	this->isLoaded = false;
	this->isMoving = false;
	this->isStored = true;
	this->isHit = false;

	//States: 0 = Idlde, 1 = Shooting;
	this->bulletState = 0;
}

Bullet::~Bullet()
{

}

int Bullet::getState() const
{
	return this->bulletState;
}


void Bullet::setBulletPos(float posX, float posY)
{
	this->eSprite.setPosition(posX, posY);
}

void Bullet::setBulletDir()
{
	this->bulletDir.x = cos(this->angle * DEGTORAD);
	this->bulletDir.y = sin(this->angle * DEGTORAD);
}

void Bullet::setDistance(float frameTime)
{
	this->distance = (bulletDir * speed * frameTime);
}

void Bullet::setAngle(float angle)
{
	this->angle = angle;
}

void Bullet::setMoving()
{
	this->bulletState = 1;
}

void Bullet::isFiring() 
{
	this->eShape.move(this->distance);
}

void Bullet::bulletMove(sf::Vector2f playerPos, float angle, float frameTime)
{
	this->setAngle(angle);
	this->setBulletDir();
	this->setDistance(frameTime);
	this->eShape.setPosition(playerPos);
}

void Bullet::bulletBoundCheck()
{
	for (int i = 0; i < BULLET_CAP; i++) {
		//Check if projectile is outside the screen. if it is. Move it.
		if (this->eShape.getPosition().y < 0 && !this->isLoaded) {
			this->bulletState = 0;
		}
		else if (this->eShape.getPosition().y > WINDOW_HEIGHT && !this->isLoaded) {
			this->bulletState = 0;
		}
		else if (this->eShape.getPosition().x < 0 && !this->isLoaded)
		{
			this->bulletState = 0;
		}
		else if (this->eShape.getPosition().x > WINDOW_WIDTH && !this->isLoaded) {
			this->bulletState = 0;
		}
	}
}

void Bullet::bulletHasHit()
{
	this->bulletState = 0;
}

void Bullet::update(float frameTime, SpaceShip playerRef)
{
	
	if (this->bulletState == 0)
		this->bulletIdleUpdate();
	if (this->bulletState == 1) {
		this->bulletShootingUpdate(playerRef, frameTime);
	}

	this->bulletBoundCheck();
	this->eSprite.setPosition(this->eShape.getPosition());

	std::cout << bulletState << std::endl;

}

void Bullet::bulletIdleUpdate()
{
	if (this->eShape.getPosition() != sf::Vector2f(WINDOW_WIDTH + 16.f, WINDOW_HEIGHT)) {
		this->eShape.setPosition(sf::Vector2f(WINDOW_WIDTH + 16.f, WINDOW_HEIGHT));
	}
	this->isLoaded = true;
}

void Bullet::bulletShootingUpdate(SpaceShip playerRef, float frameTime)
{
	if (this->isLoaded) {
		this->eShape.setPosition(playerRef.getPlayerCenter());
		this->bulletMove(playerRef.getPlayerCenter(), playerRef.getPlayerAngle(), frameTime);
		this->isLoaded = false;
	}
	this->isFiring();
}

sf::RectangleShape Bullet::getBulletShape() const
{
	return this->eShape;
}