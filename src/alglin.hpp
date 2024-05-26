#pragma once

#include <SFML/Graphics.hpp>

float euclidian_distance(sf::Vector2f a, sf::Vector2f b);
float magnitude(sf::Vector2f vec);
bool out_of_bounds_x(int x);
bool out_of_bounds_y(int y);
bool check_bounds(sf::Vector2f pos);
sf::Vector2f random_direction();
