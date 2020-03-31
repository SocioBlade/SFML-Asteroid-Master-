#pragma once
#include <string>
#include "Const.hpp"
#include <SFML\Graphics.hpp>

class Entity : public sf::Drawable
{
protected:
	Entity();
	Entity(float sizeX, float sizeY, float posX, float posY, float scaleX,
		float scaleY, float rectX, float rectY, std::string fileName);

private:
	float sizeX,
		sizeY,
		posX,
		posY,
		scaleX,
		scaleY,
		rectX,
		rectY,
		angle;

	std::string fileName;
	sf::Texture eTexture;

public:
	sf::Sprite eSprite;
	sf::RectangleShape eShape;

public:
	~Entity();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void createShape(sf::RectangleShape &shape, float sizeX, float sizeY,
		float posX, float posY, float scaleX, float scaleY);

	void createSprite(sf::Sprite &pSprite, sf::Texture &pTexture, std::string fileName,
		int rectX, int rectY, float scaleX, float scaleY);

};
