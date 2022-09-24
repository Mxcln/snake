#ifndef HEAD_NODE_H
#define HEAD_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class HeadNode
{
public:
	HeadNode(sf::Vector2f position=sf::Vector2f(0,0),sf::Vector2f direction=sf::Vector2f(0,-1));
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setDirection(float x,float y);
	void setDirection(sf::Vector2f direction);

	void move(sf::Vector2f direction);

	void rotate(float angle);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::Vector2f getDirection() const;
	sf::FloatRect getBounds() const;

    static const float Width;
	static const float Height;

private:
	sf::Sprite sprite_;
    sf::Texture texture_;
	sf::Vector2f position_;
	sf::Vector2f direction_;
};
}

#endif