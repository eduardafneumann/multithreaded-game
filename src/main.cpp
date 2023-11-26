#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <iostream>
#include <string>

#include "../include/constants.hpp"
#include "../include/objects.hpp"
#include "../include/player.hpp"
#include "../include/bot.hpp"
#include "../include/chair.hpp"
#include "../include/alglin.hpp"

bool window_is_open = false;
int score = 0;
std::vector<sf::CircleShape> objects;

std::mutex move_mutex;
std::mutex score_mutex;

void bot_thread(void *objs_ptr, void *index, void *window_is_open, void *score)
{
    std::vector<sf::CircleShape> *objs = (std::vector<sf::CircleShape> *)objs_ptr;
    int *idx = (int *)index;
    bool *open = (bool *)window_is_open;
    int *s = (int *)score;

    sf::Vector2f dir = random_direction();

    while (*open)
    {
        move_mutex.lock();
        int add_to_score = move_bot(*objs, *idx, dir);
        move_mutex.unlock();

        score_mutex.lock();
        *s += add_to_score;
        score_mutex.unlock();

        usleep(5000);
    }
}

void chair_thread(void *objs_ptr, void *index, void *window_is_open, void *score)
{
    std::vector<sf::CircleShape> *objs = (std::vector<sf::CircleShape> *)objs_ptr;
    int *idx = (int *)index;
    bool *open = (bool *)window_is_open;
    int *s = (int *)score;

    bool is_green = false;
    bool is_touching_player = false;
    while (*open)
    {
        if(maybe_turn_green((*objs)[*idx])){
            is_green = true;
        }

        move_mutex.lock();
        int add_to_score = deal_with_colision(*objs, *idx, is_green, is_touching_player);
        move_mutex.unlock();

        score_mutex.lock();
        *s += add_to_score;
        score_mutex.unlock();

        usleep(10);
    }
}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Trabalho prático de SO");
    window_is_open = true;

    create_objects(objects);

    int bot1 = BOT1;
    int bot2 = BOT2;
    int bot3 = BOT3;
    int bot4 = BOT4;
    std::thread bt1(bot_thread, &objects, &bot1, &window_is_open, &score);
    std::thread bt2(bot_thread, &objects, &bot2, &window_is_open, &score);
    std::thread bt3(bot_thread, &objects, &bot3, &window_is_open, &score);
    std::thread bt4(bot_thread, &objects, &bot4, &window_is_open, &score);

    int chair1 = CHAIR1;
    int chair2 = CHAIR2;
    int chair3 = CHAIR3;
    int chair4 = CHAIR4;
    std::thread ct1(chair_thread, &objects, &chair1, &window_is_open, &score);
    std::thread ct2(chair_thread, &objects, &chair2, &window_is_open, &score);
    std::thread ct3(chair_thread, &objects, &chair3, &window_is_open, &score);
    std::thread ct4(chair_thread, &objects, &chair4, &window_is_open, &score);

    sf::Text text;
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::Font font;
    if (!font.loadFromFile("fonts/sixty.ttf"))
    {
        std::cout << "Erro ao carregar a fonte do texto." << std::endl;
    }
    text.setFont(font);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                move_mutex.lock();
                move_player(event.key.code, objects);
                move_mutex.unlock();
            }
        }

        score_mutex.lock();
        score++;
        score_mutex.unlock();

        std::string score_str = std::to_string(score / 1000);
        text.setString("Score: " + score_str);

        window.clear();
        draw_objects(window, objects);
        window.draw(text);
        window.display();
    }

    window_is_open = false;

    bt1.join();
    bt2.join();
    bt3.join();
    bt4.join();
    ct1.join();
    ct2.join();
    ct3.join();
    ct4.join();

    return 0;
}
