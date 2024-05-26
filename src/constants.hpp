#pragma once 

#define HEIGHT 600
#define WIDTH 800

#define KEY_A 0
#define KEY_W 22
#define KEY_S 18
#define KEY_D 3

#define RADIUS 25

#define DELTA 10

#define PLAYER 0
#define BOT1 1
#define BOT2 2
#define BOT3 3
#define BOT4 4
#define CHAIR1 5
#define CHAIR2 6
#define CHAIR3 7
#define CHAIR4 8

#define CHAIR1POS sf::Vector2f(3*(WIDTH - RADIUS)/4, 3*(HEIGHT - RADIUS)/4)
#define CHAIR2POS sf::Vector2f(1*(WIDTH - RADIUS)/4, 3*(HEIGHT - RADIUS)/4)
#define CHAIR3POS sf::Vector2f(3*(WIDTH - RADIUS)/4, 1*(HEIGHT - RADIUS)/4)
#define CHAIR4POS sf::Vector2f(1*(WIDTH - RADIUS)/4, 1*(HEIGHT - RADIUS)/4)
