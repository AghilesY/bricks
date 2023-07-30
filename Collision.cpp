#include "Collision.h"
#include <iostream>
#include "math.h"

Collision::Collision(sf::RectangleShape &body): body(body), window(window)
{
    

}


Collision::~Collision()
{
}


bool Collision::checkCollision(Collision other)
{
    
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;


    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    /*float penetrationX = std::min(abs(intersectX), thisHalfSize.x + otherHalfSize.x);
    float penetrationY = std::min(abs(intersectY), thisHalfSize.y + otherHalfSize.y);

    bool signX = (deltaX >= 0.0f) ? 1 : 0;
    bool signY = (deltaY >= 0.0f) ? 1 : 0;*/


    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        
       /* //std::cout<<"("<<penetrationX <<" , "<<penetrationY<<")"<<std::endl;

        if (penetrationX < penetrationY)
        {
            return 1;
        }
        else 
        {
            return 2;
        }*/
        return 1;
    }

    return 0;
}

int Collision::checkCollision2(Collision other)
{
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {

        if (intersectX > intersectY)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }


    return 0;
}
