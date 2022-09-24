#ifndef BODY_NODE_H
#define BODY_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class BodyNode
	{
	public:
		BodyNode(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f direction = sf::Vector2f(0, -1));

		void setPosition(sf::Vector2f position);
		void setPosition(float x, float y);
		void setDirection(sf::Vector2f direction);

		void rotate(float angle);

		void render(sf::RenderWindow &window);

		sf::Vector2f getPosition() const;
		sf::Vector2f getDirection() const;
		sf::FloatRect getBounds() const;

		static const float Width;
		static const float Height;
		static const float Radius;

	private:
		sf::RectangleShape recshape_;
		sf::CircleShape cirshape_;
		sf::Vector2f position_;
		sf::Vector2f direction_;
	};
}

#endif