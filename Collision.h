#pragma once
#include <SFML\Graphics.hpp>

class Collision {
    public:
        Collision(sf::RectangleShape& body);
        ~Collision();

        void Move(float dx, float dy){body.move(dx, dy);}
        bool checkCollision(Collision other);
        int checkCollision2(Collision other); //0: pas de colision; 1:x; 2:y
        bool GetDirectionX(){return signX;}
        bool GetDirectionY(){return signY;}

        float intersectX;
        float intersectY;

        sf::Vector2f GetPosition(){return body.getPosition();}
        sf::Vector2f GetHalfSize(){return body.getSize() / 2.0f;}

    private:
        sf::RenderWindow& window;
        sf::RectangleShape& body;
        bool signX;
        bool signY;
};

