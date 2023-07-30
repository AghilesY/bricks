#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"

class Bar
{
public:
    Bar(float size, float speed, sf::RenderWindow & window);
    ~Bar();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f GetPosition(){return body.getPosition();}

    Collision GetCollision(){return Collision(body);}
private:
    sf::RenderWindow & window;
   
    sf::RectangleShape body;
    float speed;

};

