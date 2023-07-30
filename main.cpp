#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Bar.h"
#include "Brick.h"
#include <iostream>
#include <fstream>

    
static const float VIEW_HEIGHT = 512.0f;
static const float VIEW_WIDTH = 2*512.0f;
std::string numBricks, brickWidth, brickHeight, posX, posY;

void ResizeView(const sf::RenderWindow& window, sf::View& view){
    float aspectRatio = float(window.getSize().x)/ float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Bricks", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("ball.png");

    Bar bar(100.0f, 400.0f, window);
    Ball ball(&playerTexture, 10.0f, window, bar);

    std::fstream file("level.txt");
    if (!file.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1; 
    }
    std::getline(file, numBricks);
    int numBricksInt = std::stoi(numBricks);
    std::getline(file, brickWidth);

    std::getline(file, brickHeight);
    
    
    std::vector<Brick> bricks;
    for(int i=0; i < std::stoi(numBricks); i++){
        std::getline(file, posX);
        std::getline(file, posY);
        Brick brick(sf::Vector2f(std::stof(brickWidth), std::stof(brickHeight)), sf::Vector2f(std::stof(posX), std::stof(posY)), ball);
        bricks.push_back(brick);
        
    }

    //sf::Font font;
    // font.loadFromFile("Arial.ttf");
    //  sf::Text text("rompiche", font, 50);
    //    text.setPosition(sf::Vector2f(50,50));


    
    float deltaTime=0;
    if(deltaTime > 1.0f/2000.0f)
        deltaTime = 1.0f/2000.0f;
    
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime= clock.restart().asSeconds();
        

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }
        bar.Update(deltaTime);
        ball.Update(deltaTime);

    for(Brick &brk :bricks){
        brk.Update();
    }
       
        

        window.clear(sf::Color::Cyan);
        window.setView(view);
       
        bar.Draw(window);
        ball.Draw(window);
        
    for(Brick &brk :bricks){
        brk.Draw(window);
    }
        
        
        window.display();

    }
return 0;
}