#include <SFML/Graphics.hpp>

#include <memory>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "BodyNode.h"
#include "HeadNode.h"
#include "GameOverScreen.h"
#include "SettingScreen.h"

#define PI 3.14159265359

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : hitSelf_(false)
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	float distance = (Setting::game_speed+1)*3+15;
	headNode_.setPosition(sf::Vector2f(sf::Vector2f(Game::Width / 2, Game::Height / 2)));
	bodyNodes_.push_back(BodyNode(sf::Vector2f(
		Game::Width / 2,
		Game::Height / 2 + distance)));
	for (int i = 2; i < Snake::InitialSize; ++i)
	{
		bodyNodes_.push_back(BodyNode(sf::Vector2f(
			Game::Width / 2,
			Game::Height / 2 + (distance * i))));
	}
}

void sfSnake::Snake::handleInput(sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		Setting::game_pause = ! Setting::game_pause;

	if(!Setting::game_pause)
	{
		//keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			headNode_.setDirection( sf::Vector2f(0, -1));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			headNode_.setDirection( sf::Vector2f(0, 1));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			headNode_.setDirection( sf::Vector2f(-1, 0));
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			headNode_.setDirection( sf::Vector2f(1, 0));

		//mouse input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			headNode_.setDirection((sf::Vector2f)sf::Mouse::getPosition(window) - headNode_.getPosition());
	}
}

void Snake::update(sf::Time delta)
{
	if(!Setting::game_pause)
	{
		move();
		checkEdgeCollisions();
		checkSelfCollisions();
	}
}

void Snake::checkFruitCollisions(std::vector<Fruit> &fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(headNode_.getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		grow((*toRemove).getPoint());
		fruits.erase(toRemove);
	}
}

//prevent fruits from being generated in the body of snake
bool Snake::checkFruitOverlap(Fruit &fruit)   
{
	if(headNode_.getBounds().intersects(fruit.getBounds()))
		return true;
	for(const auto& node : bodyNodes_)
	{
		if(node.getBounds().intersects(fruit.getBounds()))
			return true;
	}
	return false;
}

void Snake::grow(int grow_num)
{
	for (int i = 0; i < grow_num; i++)
		bodyNodes_.push_back(BodyNode(bodyNodes_.back()));
}

unsigned Snake::getSize() const
{
	return bodyNodes_.size() + 1;
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{

	/*calculate the angle of direction vectors between head and node0,
	namely the angle of the turn,to judge whether the head of snake hit self*/
	if (((headNode_.getDirection().x) * (bodyNodes_[0].getDirection().x)) + 
		((headNode_.getDirection().y) * (bodyNodes_[0].getDirection().y)) < -1)
	{
		dieSound_.play();
		sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
		hitSelf_ = true;
		return;
	}

	//start from bodyNode_[1],because bodyNode_[0] had been judged above 
	for (decltype(bodyNodes_.size()) i = 1; i < bodyNodes_.size(); ++i)
	{
		if (headNode_.getBounds().intersects(bodyNodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			return;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	if (headNode_.getPosition().x < HeadNode::Width / 2)
		headNode_.setPosition(Game::Width- HeadNode::Width / 2, headNode_.getPosition().y);
	else if (headNode_.getPosition().x > Game::Width - HeadNode::Width / 2)
		headNode_.setPosition(HeadNode::Width / 2, headNode_.getPosition().y);
	else if (headNode_.getPosition().y < HeadNode::Height / 2)
		headNode_.setPosition(headNode_.getPosition().x, Game::Height - HeadNode::Height / 2);
	else if (headNode_.getPosition().y > Game::Height - HeadNode::Height / 2)
		headNode_.setPosition(headNode_.getPosition().x, HeadNode::Height / 2);
}


void Snake::move()
{
	for (decltype(bodyNodes_.size()) i = bodyNodes_.size() - 1; i > 0; --i)
	{
		bodyNodes_[i].setPosition(bodyNodes_.at(i - 1).getPosition());
		bodyNodes_[i].rotate((atan2(bodyNodes_[i].getDirection().x,
			bodyNodes_[i].getDirection().y)-atan2(bodyNodes_[i-1].getDirection().x,
			bodyNodes_[i-1].getDirection().y)) * 180 / PI);
		bodyNodes_[i].setDirection(bodyNodes_.at(i - 1).getDirection());
	}
	bodyNodes_[0].setPosition(headNode_.getPosition());
	bodyNodes_[0].rotate((atan2(bodyNodes_[0].getDirection().x,
			bodyNodes_[0].getDirection().y)-atan2(headNode_.getDirection().x,
			headNode_.getDirection().y)) * 180 / PI);
	bodyNodes_[0].setDirection(headNode_.getDirection());
	
	headNode_.move(headNode_.getDirection());
	headNode_.rotate(180 - atan2(headNode_.getDirection().x, 
			headNode_.getDirection().y) * 180 / PI);
}

void Snake::render(sf::RenderWindow &window)
{
	for (auto node : bodyNodes_)
		node.render(window);
	headNode_.render(window);
}