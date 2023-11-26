#pragma once

#include <SFML/Graphics.hpp>

float euclidian_distance(sf::Vector2f a, sf::Vector2f b);
float magnitude(sf::Vector2f vec);
bool out_of_bounds_x(int x);
bool out_of_bounds_y(int y);
sf::Vector2f random_direction();
bool touched_chair(sf::Vector2f pos);
