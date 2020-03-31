#include "FontHandler.h"



FontHandler::FontHandler()
{
	this->points = 0;
	this->health = 100;
	if (!font.loadFromFile("../Resources/8bitFont.ttf")) {
		// handle Error
	}
	//Setting the fonts
	this->score.setFont(font);
	this->hScore.setFont(font);
	this->hp.setFont(font);
	this->gameOver.setFont(font);

	//setting up GameOver text
	this->gameOver.setCharacterSize(52);
	this->gameOver.setPosition(WINDOW_WIDTH, -64);
	this->gameOver.setFillColor(sf::Color::White);
	this->gameOver.setString("Game Over");

	//Setting up score UI
	this->score.setCharacterSize(52);
	this->score.setScale(sf::Vector2f(0.75f, 0.75f));
	this->score.setString("Score: " + std::to_string(points));
	this->score.setFillColor(sf::Color::White);
	this->score.setPosition(20.f, 40.f);
	
	//Setting up highscore UI
	this->hScore.setCharacterSize(42);
	this->hScore.setScale(sf::Vector2f(1.f, 1.f));
	this->hScore.setString("Best: " + std::to_string(highScore));
	this->hScore.setFillColor(sf::Color::White);
	//Initial position is outside screen.
	this->hScore.setPosition(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Setting up HP UI
	this->hp.setString("HP: " + std::to_string(health));
	this->hp.setFillColor(sf::Color::White);
	this->hp.setPosition(20.f, 10.f);

	//this->score.setFont(font);

	//Setting up the End screen panel
	this->endScreen.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	this->endScreen.setFillColor(sf::Color::Black);
	//Initial position is outside the screen
	this->endScreen.setPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
}


FontHandler::~FontHandler()
{
}

void FontHandler::setScore()
{
	this->points++;
}

void FontHandler::setLife()
{
	this->health--;
}

void FontHandler::update()
{
	this->hp.setString("Hp: " + std::to_string(health));
	this->score.setString("Score: " + std::to_string(points));
}

void FontHandler::displayFinalScore()
{
	//Read highscore file 
	std::ifstream readFile;
	readFile.open("../Resources/HighScore.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			//Set value from file to highscore var
			readFile >> highScore;
		}
	}
	readFile.close();

	std::ofstream writeFile("../Resources/HighScore.txt");
	if (writeFile.is_open())
	{
		if (points > highScore)
			highScore = points;
		writeFile << highScore;
	}
	writeFile.close();

	this->hScore.setString("Best: " + std::to_string(highScore));

	endScreen.setPosition(sf::Vector2f(0, 0));
	hp.setPosition(WINDOW_WIDTH, -64);
	gameOver.setPosition((WINDOW_WIDTH / 2) - 156, (WINDOW_HEIGHT / 2) - 186);
	score.setPosition((WINDOW_WIDTH / 2) - 186, (WINDOW_HEIGHT / 2) - 128);
	score.setScale(sf::Vector2f(1.5f, 1.5f));
	hScore.setPosition((WINDOW_WIDTH / 2) - 120, WINDOW_HEIGHT / 2);
}

void FontHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(endScreen, states);
	target.draw(gameOver, states);
	target.draw(hp, states);
	target.draw(score, states);
	target.draw(hScore, states);
}
