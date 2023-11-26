#include "../include/move.hpp"

#include "../include/constants.hpp"
#include "../include/alglin.hpp"
#include <vector>

void move_bot(std::vector<sf::CircleShape>& bots, int idx, sf::Vector2f& dir, bool& game_ended)
{
    sf::Vector2f pos = bots[idx].getPosition();
    pos += dir;

    if (out_of_bounds_x(pos.x))
    {
        pos.x = pos.x - 2 * dir.x;
        dir.x = -dir.x;
    }
    if (out_of_bounds_y(pos.y))
    {
        pos.y = pos.y - 2 * dir.y;
        dir.y = -dir.y;
    }

    for (int i = 0; i < bots.size(); i++)
    {
        if(i==idx) { continue; }

        float dist = euclidian_distance(pos, bots[i].getPosition());

        if(dist < 2*RADIUS) { //touched 
            if(i==PLAYER){
                game_ended = true;
            }
            sf::Vector2f a = pos - bots[i].getPosition();
            a = a * (float)(1 / magnitude(a));
            pos += a;
            dir = a;
        }
    }

    bots[idx].setPosition(pos);
}

bool check_bounds(sf::Vector2f pos)
{
    if (out_of_bounds_x(pos.x) || out_of_bounds_y(pos.y))
    {
        return false;
    }
    return true;
}

void move_player(sf::Keyboard::Key key, std::vector<sf::CircleShape>& objects)
{

    sf::Vector2f pos = objects[PLAYER].getPosition();

    switch (key)
    {
    case 0:
        pos.x -= DELTA;
        break;
    case 3:
        pos.x += DELTA;
        break;
    case 18:
        pos.y += DELTA;
        break;
    case 22:
        pos.y -= DELTA;
        break;
    }

    if (check_bounds(pos))
    {
        objects[PLAYER].setPosition(pos);
    }
}