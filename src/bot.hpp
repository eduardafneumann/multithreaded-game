#pragma once

#include <SFML/Graphics.hpp>

int move_bot(std::vector<sf::CircleShape>& objects, int idx, sf::Vector2f& dir);
bool is_bot(int idx);