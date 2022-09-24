#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "SettingScreen.h"

using namespace sfSnake;

const int GameScreen::fruits_num = 8;

GameScreen::GameScreen() : snake_()
{
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	for(int i=fruits_.size();i<fruits_num;i++)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruits_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	//set background (color and grid)
	if(Setting::background_color==sf::Color::White)
	{
		if(Setting::grid_switch == ON )
		{
			if(Setting::grid_color == sf::Color::White)
				tex_.loadFromFile("pic/White-White.png");
			else if(Setting::grid_color == sf::Color::Black)
				tex_.loadFromFile("pic/White-Black.png");
			else if(Setting::grid_color == sf::Color(90,57,18))
				tex_.loadFromFile("pic/White-Brown.png");
		}
		else tex_.loadFromFile("pic/White-White.png");
	}
	else if(Setting::background_color==sf::Color::Black)
	{
		if(Setting::grid_switch == ON )
		{
			if(Setting::grid_color == sf::Color::White)
				tex_.loadFromFile("pic/Black-White.png");
			else if(Setting::grid_color == sf::Color::Black)
				tex_.loadFromFile("pic/Black-Black.png");
			else if(Setting::grid_color == sf::Color(90,57,18))
				tex_.loadFromFile("pic/Black-Brown.png");
		}
		else tex_.loadFromFile("pic/Black-Black.png");
	}
	else if(Setting::background_color==sf::Color(90,57,18))
	{
		if(Setting::grid_switch == ON )
		{
			if(Setting::grid_color == sf::Color::White)
				tex_.loadFromFile("pic/Brown-White.png");
			else if(Setting::grid_color == sf::Color::Black)
				tex_.loadFromFile("pic/Brown-Black.png");
			else if(Setting::grid_color == sf::Color(90,57,18))
				tex_.loadFromFile("pic/Brown-Brown.png");
		}
		else tex_.loadFromFile("pic/Brown-Brown.png");
	}

	sprite_.setTexture(tex_);
	window.draw(sprite_);

	snake_.render(window);

	for (auto& fruit : fruits_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(std::rand());
	static std::uniform_int_distribution<int> colorDistribution(0,80000);
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - HeadNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - HeadNode::Height);
	
	//set random color
	sf::Color randomColor;
	switch(colorDistribution(engine)%8)
	{
		case 0: randomColor=sf::Color::Black;
			break;
		case 1: randomColor=sf::Color(90,57,18); //Brown
			break;
		case 2:
		case 3: randomColor=sf::Color::Red;
			break;
		case 4:
		case 5: randomColor=sf::Color::Blue;
			break;
		case 6:
		case 7: randomColor=sf::Color::Green;
			break;
	}

	//prevent overlap
	while(1)
	{
		Fruit fruit = Fruit(randomColor,sf::Vector2f(xDistribution(engine), yDistribution(engine)));
		if(!snake_.checkFruitOverlap(fruit))
		{
			fruits_.push_back(fruit);
			break;
		}
	}
}

