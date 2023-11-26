#pragma once

#include <SFML/Graphics.hpp>

void move_bot(std::vector<sf::CircleShape>& bots, int idx, sf::Vector2f& dir, bool& game_ended);
void move_player(sf::Keyboard::Key key, std::vector<sf::CircleShape> &objects);