#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include "Const.hpp"

class FontHandler : public sf::Drawable
{
public:
	FontHandler();
	~FontHandler();

	void setScore();
	void setLife();
	void update();
	void displayFinalScore();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	sf::Font font;
	sf::Text score;
	sf::Text hScore;
	sf::Text hp;
	sf::Text gameOver;
	sf::RectangleShape endScreen;
	int points;
	int highScore;
	int health;
};

