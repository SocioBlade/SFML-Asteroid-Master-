#include "Asteroids.hpp"



Asteroids::Asteroids()
	:Entity(40.f, 40.f, -WINDOW_WIDTH, -WINDOW_HEIGHT, 2.f, 2.f,
		48.f, 48.f, "../Resources/Asteroids&targets.png")
{
	//Create Event
	srand(unsigned int(time(NULL)));
	this->isHit = true;
	this->givePoint = false;
	this->isSpawning = false;
	this->posX = WINDOW_WIDTH;
	this->posY = WINDOW_HEIGHT;
	this->dirX = static_cast<float>(rand()%360);
	this->dirY = static_cast<float>(rand()%360);
	this->angle = static_cast<float>(rand() % 360);
	this->maxSpeed = 0;
	this->imageIndex = 0;
	this->timer = 0.f;
	this->timerMax = 4.f;
	this->spawnTimer = 0.f;

}

Asteroids::~Asteroids()
{
}

void Asteroids::update(float frameTime)
{
	switch (imageIndex)
	{
	case 1:
		this->eSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
		break;
	case 2:
		this->eSprite.setTextureRect(sf::IntRect(48, 0, 48, 48));
		break;
	case 3:
		this->eSprite.setTextureRect(sf::IntRect(96, 0, 48, 48));
		break;
	default:
		break;
	}
	//Step Event
	//asteroid movement
	if (!isHit) {
		this->dirX += cos(this->angle * DEGTORAD)*0.01f;
		this->dirY += sin(this->angle * DEGTORAD)*0.01f;
	

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
		if (this->rotateCheck >= 5) {
			this->eShape.rotate(+0.3f);
		}
		if (this->rotateCheck < 5) {
			this->eShape.rotate(-0.3f);
		}

		eSprite.setPosition(eShape.getPosition());
		eSprite.setRotation(eShape.getRotation());
		
	}
	//If hit, wait, then respawn with warning
	if (isHit) {
		eSprite.setTextureRect(sf::IntRect(144, 0, 48, 48));
		this->timer += frameTime;
		if (this->timer >= timerMax) {
			timer = 0;
			if (spawnTimer == 0) {
				setPosRotSpd(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT,
					static_cast<float>(rand() % 360), static_cast<float>(rand() % 360),
					static_cast<float>(rand() % 360), static_cast<float>(rand() % 2 + 1));
			}
			spawnTimer += frameTime;
			if (spawnTimer <= 0.02f) {
				eSprite.setPosition(posX, posY);
			}
			if (spawnTimer >= 0.03f) {
				spawnTimer = 0;
				this->imageIndex = rand() % 3 + 1;
				isHit = false;
			}
			
		}
		//Debug print of the spawn timer
		std::cout << spawnTimer << std::endl;
	}
}

void Asteroids::setPosRotSpd(int posX, int posY, float dirX, float dirY,
	float angle, float maxSpeed)
{
	this->rotateCheck = rand() % 10 +1;
	this->posX = static_cast<float>(posX);
	this->posY = static_cast<float>(posY);
	this->dirX = dirX;
	this->dirY = dirY;
	this->angle = angle;
	this->maxSpeed = maxSpeed;
	this->eShape.rotate(angle);
}

sf::RectangleShape Asteroids::getAsteroidShape()
{
	return this->eShape;
}

void Asteroids::bBoxDraw(sf::RenderWindow & window)
{
	window.draw(eShape);
}

bool Asteroids::getGivePoint()
{
	return this->givePoint;
}

void Asteroids::setGivePoint()
{
	this->givePoint = false;
}