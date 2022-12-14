#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{

	class Fruit
	{
	public:
		Fruit(sf::Color color = sf::Color::White, sf::Vector2f position = sf::Vector2f(0, 0));

		void render(sf::RenderWindow &window);

		sf::FloatRect getBounds() const;

		int getPoint();

	private:
		sf::CircleShape shape_;
		sf::Color color_;

		static const float Radius;
	};
}

#endif