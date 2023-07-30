#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

static const float windowWidth = 2 * 512.0f;
static const float windowHeight = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(windowHeight * aspectRatio, windowHeight);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Editor", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, windowHeight));

    int numRows = 5;
    int numCols = 10;

    struct
    {
        float x = 20;
        float y = 20;
    } start;

    sf::Vector2f startPosition(start.x - window.getSize().x / 2.0f, start.y - window.getSize().y / 2.0f);

    const int brickZoneHeight = windowHeight / 3;
    int brickZoneWidth = windowWidth - 2 * static_cast<int>(start.x);
    int brickWidth = brickZoneWidth / numCols;
    int brickHeight = brickZoneHeight / numRows;
    int numBricks=0;

    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(100, 10));
    bar.setOrigin(bar.getSize() / 2.0f);
    bar.setFillColor(sf::Color::Red);
    bar.setPosition(0, 150);

    sf::CircleShape ball;
    ball.setRadius(5);
    ball.setFillColor(sf::Color::Blue);
    ball.setOrigin(ball.getRadius(), ball.getRadius());
    ball.setPosition(0, 0);

    std::vector<std::vector<sf::RectangleShape>> bricks(numRows, std::vector<sf::RectangleShape>(numCols));

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            sf::Vector2f position = startPosition + sf::Vector2f(j * (brickWidth + 1.0f), i * (brickHeight + 1.0f));
            sf::RectangleShape brick(sf::Vector2f(brickWidth, brickHeight));
            brick.setPosition(position);
            brick.setFillColor(sf::Color::Green);
            bricks[i][j] = brick;
        }
    }

    std::ofstream file("level.txt", std::ofstream::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1; // Exit the program with an error code
    }

    bool mouseLeftButtonPressed = false;
    bool prevMouseLeftButtonState = false; // To track the previous state of the left mouse button

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::MouseButtonPressed:
                if (evnt.mouseButton.button == sf::Mouse::Left)
                {
                    mouseLeftButtonPressed = true;
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (evnt.mouseButton.button == sf::Mouse::Left)
                {
                    mouseLeftButtonPressed = false;
                }
                break;
            case sf::Event::Closed:
                for (int i = 0; i < numRows; ++i)
                {
                    for (int j = 0; j < numCols; ++j)
                    {
                        if (bricks[i][j].getFillColor() == sf::Color::Red)
                        {
                            numBricks++;
                        }
                    }
                }

                file << std::to_string(numBricks) << std::endl;
                file << std::to_string(brickWidth) << std::endl;
                file << std::to_string(brickHeight) << std::endl;

                for (int i = 0; i < numRows; ++i)
                {
                    for (int j = 0; j < numCols; ++j)
                    {
                        if (bricks[i][j].getFillColor() == sf::Color::Red)
                        {
                            file << bricks[i][j].getPosition().x << std::endl;
                            file << bricks[i][j].getPosition().y << std::endl;
                        }
                    }
                }

                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    numCols--;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    numCols++;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    numRows--;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    numRows++;

                numRows = std::max(numRows, 1);
                numCols = std::max(numCols, 1);

                brickZoneWidth = windowWidth - 2 * static_cast<int>(start.x);
                brickWidth = brickZoneWidth / numCols;
                brickHeight = brickZoneHeight / numRows;

                bricks.resize(numRows);
                for (int i = 0; i < numRows; ++i)
                {
                    bricks[i].resize(numCols);
                }

                for (int i = 0; i < numRows; ++i)
                {
                    for (int j = 0; j < numCols; ++j)
                    {
                        sf::Vector2f position = startPosition + sf::Vector2f(j * (brickWidth + 1.0f), i * (brickHeight + 1.0f));
                        sf::RectangleShape brick(sf::Vector2f(brickWidth, brickHeight));
                        brick.setPosition(position);
                        brick.setFillColor(sf::Color::Green);
                        bricks[i][j] = brick;
                    }
                }

                std::cout << numCols << std::endl;
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        // Check if the mouse is on a brick and change its color
        if (mouseLeftButtonPressed && !prevMouseLeftButtonState)
        {
            int mousePositionX = sf::Mouse::getPosition(window).x - window.getSize().x / 2;
            int mousePositionY = sf::Mouse::getPosition(window).y - window.getSize().y / 2;
            sf::Vector2i mousePosition = sf::Vector2i(mousePositionX, mousePositionY);

            for (int i = 0; i < numRows; ++i)
            {
                for (int j = 0; j < numCols; ++j)
                {
                    if (bricks[i][j].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                    {
                        if (bricks[i][j].getFillColor() == sf::Color::Green)
                        {
                            bricks[i][j].setFillColor(sf::Color::Red);
                        }
                        else if (bricks[i][j].getFillColor() == sf::Color::Red)
                        {
                            bricks[i][j].setFillColor(sf::Color::Green);
                        }
                    }
                }
            }
        }

        prevMouseLeftButtonState = mouseLeftButtonPressed;

        window.clear();

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                window.draw(bricks[i][j]);
            }
        }
        window.draw(bar);
        window.draw(ball);

        window.setView(view);
        window.display();
    }

    file.close();
    return 0;
}
