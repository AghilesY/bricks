#include "Brick.h"
#include "Ball.h"

Brick::Brick(sf::Vector2f size,sf::Vector2f position, Ball &ball) : ball(ball)
{
    this->body = body;
    this->isDestroyed = isDestroyed;

    body.setPosition(position);
    body.setOrigin(size / 2.0f);
    body.setSize(size);
    body.setFillColor(sf::Color::Green);


    isDestroyed = false;
}

Brick::~Brick()
{
}

void Brick::Draw(sf::RenderWindow &window)
{
    if (!isDestroyed)
    {
        // std::cout<<ball.GetCollision().checkCollision(body)<<std::endl;
        window.draw(body);
    }
}

void Brick::Update()
{
    if (!isDestroyed)
    {
        switch (GetCollision().checkCollision2(ball.GetCollision()))
        {
        case 1:
            ball.bounceX();
            isDestroyed = true;
            break;
        case 2:
            ball.bounceY();
            isDestroyed = true;
            break;
        default:
            break;
        }
    }
    /*if (!isDestroyed && GetCollision().checkCollision(ball.GetCollision()))
    {
        //ball.Bounce();
        isDestroyed = true;
        std::cout << body.getPosition().x << std::endl;
    }*/
}
