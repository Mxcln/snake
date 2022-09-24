#include <SFML/Graphics.hpp>
#include<cmath>

#include "HeadNode.h"
#include "SettingScreen.h"

using namespace sfSnake;

const float HeadNode::Width = 22.f;
const float HeadNode::Height =22.f;

HeadNode::HeadNode(sf::Vector2f position,sf::Vector2f direction)
: position_(position),direction_(direction)
{
    texture_.loadFromFile("pic/head.jpg");
    sprite_.setTexture(texture_);
    sprite_.setOrigin(Width/2,Height/2);
    sprite_.setPosition(position);
    
}

void HeadNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	sprite_.setPosition(position_);
}

void HeadNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	sprite_.setPosition(position_);
}

void HeadNode::setDirection(float x,float y)
{
	direction_.x=x;
	direction_.y=y;
}
void HeadNode::setDirection(sf::Vector2f direction)
{
	direction_=direction;
}


void HeadNode::move(sf::Vector2f dir)
{
	float Distance = (Setting::game_speed+1)*3+15;
	float hypotenuse = std::pow(dir.x*dir.x+dir.y*dir.y,0.5);
	position_.x += Distance*(dir.x)/hypotenuse;
	position_.y += Distance*(dir.y)/hypotenuse;
	sprite_.setPosition(position_);
}

void HeadNode::rotate(float angle)
{
	sprite_.setRotation(angle);
}

sf::FloatRect HeadNode::getBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f HeadNode::getPosition() const
{
	return position_;
}

sf::Vector2f HeadNode::getDirection() const
{
	return direction_;
}

void HeadNode::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}