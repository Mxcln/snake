#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "SettingScreen.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Color color, sf::Vector2f position)
{
	color_ = color;
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(color);
	shape_.setOutlineColor(Setting::background_color == sf::Color::Black
							   ? sf::Color::White
							   : sf::Color::Black);
	shape_.setOutlineThickness(-1.f);
}

void Fruit::render(sf::RenderWindow &window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

int sfSnake::Fruit::getPoint()
{
	if (color_ == sf::Color::Black || color_ == sf::Color(90, 57, 18))
		return 0;
	else if (color_ == sf::Color::Red)
		return 3;
	else if (color_ == sf::Color::Blue)
		return 2;
	else if (color_ == sf::Color::Green)
		return 1;
	else
		return -1;
}