#include "Entity.h"
#include "Const.hpp"


Entity::Entity()
{
}

Entity::Entity(float sizeX, float sizeY, float posX, float posY, float scaleX,
	float scaleY, float rectX, float rectY, std::string fileName)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->posX = posX;
	this->posY = posY;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->rectX = rectX;
	this->rectY = rectY;
	this->fileName = fileName;
	this->angle = 0;

	createShape(eShape, sizeX, sizeY, posX, posY, scaleX, scaleY);
	createSprite(eSprite, eTexture, fileName, rectX, rectY, scaleX, scaleY);
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->eSprite, states);
	//Debug draw bBox
	//target.draw(this->eShape, states);
}

void Entity::createShape(sf::RectangleShape & shape, float sizeX, float sizeY,
	float posX, float posY, float scaleX, float scaleY)
{
	shape.setSize(sf::Vector2f(sizeX, sizeY));
	shape.setScale(sf::Vector2f(scaleX, scaleY));
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(sizeX / 2, sizeY / 2);
	shape.setPosition(posX, posY);
}

void Entity::createSprite(sf::Sprite &pSprite, sf::Texture &pTexture, std::string fileName,
	int rectX, int rectY, float scaleX, float scaleY)
{
	pTexture.loadFromFile(fileName);
	pSprite.setTexture(pTexture);
	pSprite.setTextureRect(sf::IntRect(0, 0, rectX, rectY));
	pSprite.setOrigin(rectX / 2, rectY / 2);
	pSprite.setScale(sf::Vector2f(scaleX, scaleY));
}