#include "../include/alglin.hpp"

#include "../include/constants.hpp"
#include <cmath>

float euclidian_distance(sf::Vector2f a, sf::Vector2f b)
{
    float dist = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    return sqrt(dist);
}

bool out_of_bounds_x(int x)
{
    return x < 0 || x > WIDTH - RADIUS;
}

bool out_of_bounds_y(int y)
{
    return y < 0 || y > HEIGHT - RADIUS;
}

bool touched_chair(sf::Vector2f pos)
{
    // if (euclidian_distance(CHAIRPOS, pos) < 2 * RADIUS)
    // {
    //     return true;
    // }
    return false;
}

float magnitude(sf::Vector2f vec)
{
    return euclidian_distance(vec, sf::Vector2f(0, 0));
}

sf::Vector2f random_direction()
{

    int x, y;
    x = y = 0;

    while (x == y)
    {
        x = rand() % 5;
        y = rand() % 5;
    }
    x++;
    y++;
    sf::Vector2f dir(x, y);
    dir /= magnitude(dir);

    return dir;
}