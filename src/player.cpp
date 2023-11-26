#include "../include/player.hpp"

#include "../include/alglin.hpp"
#include "../include/constants.hpp"
#include "../include/chair.hpp"
#include <cmath>

sf::Vector2f add_delta(sf::Vector2f pos, sf::Keyboard::Key key, int delta){
    sf::Vector2f new_pos = pos;

    switch (key)
    {
    case KEY_A:
        new_pos.x = pos.x - delta;
        break;
    case KEY_D:
        new_pos.x = pos.x + delta;
        break;
    case KEY_S:
        new_pos.y = pos.y + delta;
        break;
    case KEY_W:
        new_pos.y = pos.y - delta;
        break;
    }

    return new_pos;
}

void move_player(sf::Keyboard::Key key, std::vector<sf::CircleShape> &objects)
{

    sf::Vector2f pos = objects[PLAYER].getPosition();

    sf::Vector2f new_pos = add_delta(pos, key, DELTA);

    if (check_bounds(new_pos))
    {
        if (touched_chair(new_pos))
        {
            int chair = closest_chair(pos);
            sf::Vector2f chair_pos = objects[chair].getPosition();
            
            int dx = abs(pos.x - chair_pos.x);
            int dy = abs(pos.y - chair_pos.y);
            int const_dist = key == KEY_S || key == KEY_W ? dx : dy;
            int var_dist = key == KEY_S || key == KEY_W ? dy : dx;

            int new_delta = var_dist - sqrt(4 * RADIUS * RADIUS - const_dist * const_dist);
            new_pos = add_delta(pos, key, new_delta);
        }
        objects[PLAYER].setPosition(new_pos);
    }
}