#include "../include/chair.hpp"

#include "../include/constants.hpp"
#include "../include/alglin.hpp"
#include "../include/bot.hpp"

int closest_chair(sf::Vector2f pos)
{
    float d1 = euclidian_distance(CHAIR1POS, pos);
    float d2 = euclidian_distance(CHAIR2POS, pos);
    float d3 = euclidian_distance(CHAIR3POS, pos);
    float d4 = euclidian_distance(CHAIR4POS, pos);

    float m = std::min(d1, std::min(d2, std::min(d3, d4)));

    if (m == d1)
    {
        return CHAIR1;
    }
    else if (m == d2)
    {
        return CHAIR2;
    }
    else if (m == d3)
    {
        return CHAIR3;
    }
    else
    {
        return CHAIR4;
    }
}

bool touched_chair(sf::Vector2f pos)
{

    if (euclidian_distance(CHAIR1POS, pos) < 2 * RADIUS)
    {
        return true;
    }
    if (euclidian_distance(CHAIR2POS, pos) < 2 * RADIUS)
    {
        return true;
    }
    if (euclidian_distance(CHAIR3POS, pos) < 2 * RADIUS)
    {
        return true;
    }
    if (euclidian_distance(CHAIR4POS, pos) < 2 * RADIUS)
    {
        return true;
    }
    return false;
}

bool maybe_turn_green(sf::CircleShape& chair){
    int chance = rand() % 100000;
    if (chance == 34)
    {
        chair.setFillColor(sf::Color::Green);
        return true;
    }
    return false;
}

int deal_with_colision(std::vector<sf::CircleShape>& objects, int index, bool& is_green, bool& is_touching_player){
    int add_to_score = 0;

    float player_dist = euclidian_distance(objects[index].getPosition(), objects[PLAYER].getPosition());
    if(player_dist <= 2*(RADIUS+1) && !is_touching_player && is_green){
        objects[index].setFillColor(sf::Color::Red);
        is_green = false;
        is_touching_player = true;
        add_to_score += 10000;
    }
    if(is_touching_player && player_dist > 2*(RADIUS+1)){
        is_touching_player = false;
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if(i==index) { continue; }

        float dist = euclidian_distance(objects[index].getPosition(), objects[i].getPosition());

        if(dist <= 2*(RADIUS+1) && is_green && is_bot(i)) { //touched 
            objects[index].setFillColor(sf::Color::Red);
            is_green = false;
        }
    }
    return add_to_score;
}