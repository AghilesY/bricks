#include "Bar.h"
#include <iostream>

Bar::Bar(float size, float speed, sf::RenderWindow & window): window(window)
{
    this->speed = speed;
    
    body.setSize(sf::Vector2f(size, 10));
    body.setFillColor(sf::Color::Red);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(0,150);

}

Bar::~Bar()
{
}

void Bar::Update(float deltaTime)
{

    sf::Vector2f movement(0.0f, 0.0f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        movement.x+=speed*deltaTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        movement.x-=speed * deltaTime;
    }

    float intersectLeft= (body.getPosition().x - body.getSize().x / 2.0f) - window.getSize().x /2.0f;
    float intersectRight= (body.getPosition().x + body.getSize().x / 2.0f) - window.getSize().x /2.0f;


    if(intersectLeft<-float(window.getSize().x)){  //intersectLeft<-1024.0f
        float penetrationLeft = float(window.getSize().x) /2.0f - (body.getSize().x/ 2.0f - body.getPosition().x );
        
        body.move(-penetrationLeft,0);
    }
    else if(intersectRight>0.0f){
        float penetrationRight = float(window.getSize().x) /2.0f - (body.getSize().x/ 2.0f + body.getPosition().x );
        
        body.move(penetrationRight,0);
    }
    body.move(movement);   
}

void Bar::Draw(sf::RenderWindow& window){
    window.draw(body);
}