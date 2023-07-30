#include "Ball.h"
#include <iostream>
#include <math.h>
#include "Bar.h"
#include "Brick.h"
using namespace std;

Ball::Ball(sf::Texture *Texture, float radius, sf::RenderWindow & window, Bar &bar): bar(bar), window_(window)
{
    this->Vx = Vx;
    this->Vy = Vy;
    this->isFail = isFail;
    body.setSize(sf::Vector2f(radius, radius));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(sf::Vector2f(0.0f, 0.0f));
    body.setTexture(Texture);
    isFail = false;
}

Ball::~Ball()
{
}

void Ball::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    //

    float intersectLeft = (body.getPosition().x - body.getSize().x/2.0f) + float(window_.getSize().x)/2.0f;
    float intersectRight = (body.getPosition().x + body.getSize().x / 2.0f) - float(window_.getSize().x)/2.0f;
    float intersectTop = (body.getPosition().y - body.getSize().y / 2.0f) + float(window_.getSize().y)/2.0f;
    float intersectBottom = (body.getPosition().y + body.getSize().y / 2.0f) - float(window_.getSize().y)/2.0f;


    /*if (intersectLeft < -float(window.getSize().x))
    { // intersectLeft<-1024.0f
        float penetrationLeft = float(window.getSize().x) / 2.0f - (body.getSize().x / 2.0f - body.getPosition().x);

        body.move(-penetrationLeft, 0);
    }
    else if (intersectRight > 0.0f)
    {
        float penetrationRight = float(window.getSize().x) / 2.0f - (body.getSize().x / 2.0f + body.getPosition().x);

        body.move(penetrationRight, 0);
    }*/
    
    if ( intersectRight>= 0 || intersectLeft <= 0)
    {

        //body.move(abs(intersectLeft),0);
        Vx *= -1.0;
        
    }
    else if (intersectTop <= 0)
    {
        Vy *= -1.0f;
    }
    else if(bar.GetCollision().checkCollision(body)){
        Vx+= (GetPosition().x - bar.GetPosition().x);
        Vy=-sqrtf(norm*norm - Vx*Vx);
        
    }
    else if(intersectBottom >= 0){
        isFail = true;
       
    }
    movement.x += Vx * deltaTime;
    movement.y += Vy * deltaTime;
    body.move(movement);
}

void Ball::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}

void Ball::setSpeed(float Vxx, float Vyy)
{
    this->Vx = Vxx;
    this->Vy = Vyy;
}
