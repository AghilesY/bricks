#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Ball.h"

class Brick
{
public:
    Brick(sf::Vector2f size, sf::Vector2f position, Ball &ball);

    ~Brick();

    Collision GetCollision() { return Collision(body); }
    void Draw(sf::RenderWindow &window);
    float getPositionX(){return Position.x;}

    Brick &operator=(const Brick &other)
    {
        if (this != &other)
        {
            // Perform deep copy of members
            // Example: member = other.member;
        }
        return *this;
    }

    void Update();

private:
    sf::RectangleShape body;
    sf::Vector2f Position;
    sf::Vector2f size;

    // sf::RenderWindow & window;
    Ball &ball;

    // float width=50;
    // float height=300;

    bool isDestroyed;
};