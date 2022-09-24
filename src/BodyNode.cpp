#include <SFML/Graphics.hpp>
#include <cmath>

#include "Fruit.h"
#include "BodyNode.h"
#include "SettingScreen.h"

using namespace sfSnake;

const float BodyNode::Width = 20.f;
const float BodyNode::Height = 10.f;
const float BodyNode::Radius = 10.f;

BodyNode::BodyNode(sf::Vector2f position, sf::Vector2f direction)
	: position_(position), direction_(direction)
{
	recshape_.setOrigin(sf::Vector2f(BodyNode::Radius, BodyNode::Radius - Height / 2));
	recshape_.setPosition(position_);
	recshape_.setFillColor(sf::Color::Black);
	recshape_.setSize(sf::Vector2f(BodyNode::Width, BodyNode::Height));
	recshape_.setOutlineColor(Setting::background_color == sf::Color::Black
								  ? sf::Color::White
								  : sf::Color::Black);
	recshape_.setOutlineThickness(-1.f);

	cirshape_.setOrigin(sf::Vector2f(BodyNode::Radius, BodyNode::Radius));
	cirshape_.setPosition(position_);
	cirshape_.setFillColor(sf::Color::Yellow);
	cirshape_.setRadius(Radius);
	cirshape_.setOutlineColor(sf::Color(255,165,0));
	cirshape_.setOutlineThickness(-1.f);
}

void BodyNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	recshape_.setPosition(position_);
	cirshape_.setPosition(position_);
}

void BodyNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	recshape_.setPosition(position_);
	cirshape_.setPosition(position_);
}

void BodyNode::setDirection(sf::Vector2f direction)
{
	direction_ = direction;
}

void BodyNode::rotate(float angle)
{
	recshape_.rotate(angle);
}

sf::FloatRect BodyNode::getBounds() const
{
	return cirshape_.getGlobalBounds();
}

sf::Vector2f BodyNode::getPosition() const
{
	return position_;
}

sf::Vector2f BodyNode::getDirection() const
{
	return direction_;
}

void BodyNode::render(sf::RenderWindow &window)
{
	window.draw(cirshape_);
	window.draw(recshape_);
}