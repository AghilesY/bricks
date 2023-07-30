#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Collision.h"
#include "Bar.h"

class Ball
{
public:
    Ball(sf::Texture *Texture, float radius, sf::RenderWindow & window, Bar & bar);
    ~Ball();

    sf::Vector2f GetPosition(){ return body.getPosition();}
    void Bounce(Collision other);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void bounceX(){Vx*=-1;}
    void bounceY(){Vy*=-1;}
    void setSpeed(float Vx , float Vy);
    float getVy(){return Vy;}
    float getVx(){return Vx;}
    Collision GetCollision(){return Collision(body);}
    bool checkFail(){return isFail;}

private:
    sf::RenderWindow & window_;
    bool isFail;
    Bar & bar;
    sf::RectangleShape body;
    sf::RenderWindow window;
    //float maxSpeed;
    float deltaTime;
    
    float Vy =-150;//float(rand()) / float(RAND_MAX) * 250.0f;
    float Vx =100;// 250;//

    float norm=sqrtf(Vx*Vx + Vy*Vy);

    float angle = atan2(Vy, Vx);
};

