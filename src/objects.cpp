#include "../include/objects.hpp"

#include "../include/constants.hpp"

void draw_objects(sf::RenderWindow &window, std::vector<sf::CircleShape> &objects)
{
    for (auto obj : objects)
    {
        window.draw(obj);
    }
}

void create_objects(std::vector<sf::CircleShape> &objects)
{
    sf::CircleShape bot1(RADIUS);
    bot1.setFillColor(sf::Color::Yellow);
    bot1.setPosition(0, 0);

    sf::CircleShape bot2(RADIUS);
    bot2.setFillColor(sf::Color::Yellow);
    bot2.setPosition(WIDTH - RADIUS, 0);

    sf::CircleShape bot3(RADIUS);
    bot3.setFillColor(sf::Color::Yellow);
    bot3.setPosition(WIDTH - RADIUS, HEIGHT - RADIUS);

    sf::CircleShape bot4(RADIUS);
    bot4.setFillColor(sf::Color::Yellow);
    bot4.setPosition(0, HEIGHT - RADIUS);

    sf::CircleShape player(RADIUS);
    player.setFillColor(sf::Color::Blue);
    player.setPosition((WIDTH - RADIUS) / 2, (HEIGHT - RADIUS) / 2);

    objects.push_back(bot1);
    objects.push_back(bot2);
    objects.push_back(bot3);
    objects.push_back(bot4);
    objects.push_back(player);
}