#pragma once

#include <SFML/Graphics.hpp>

bool touched_chair(sf::Vector2f pos);
int closest_chair(sf::Vector2f pos);
bool maybe_turn_green(sf::CircleShape& chair);
int deal_with_colision(std::vector<sf::CircleShape>& objects, int index, bool& is_green, bool& is_touching_player);