#include "../include/bot.hpp"

#include "../include/alglin.hpp"
#include "../include/constants.hpp"

int move_bot(std::vector<sf::CircleShape>& objects, int idx, sf::Vector2f& dir)
{
    sf::Vector2f pos = objects[idx].getPosition();
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

    int add_to_score = 0;
    for (int i = 0; i < objects.size(); i++)
    {
        if(i==idx) { continue; }

        float dist = euclidian_distance(pos, objects[i].getPosition());

        if(dist < 2*RADIUS) { //touched 
            
            sf::Vector2f a = pos - objects[i].getPosition();
            a = a * (float)(1 / magnitude(a));
            pos += a;
            dir = a;

            if(i==PLAYER){
                add_to_score -= 1000;
            }
        }
    }

    objects[idx].setPosition(pos);
    return add_to_score;
}

bool is_bot(int idx){
    if(idx == BOT1 || idx == BOT2 || idx == BOT3 || idx == BOT4){
        return true;
    }
    return false;
}
