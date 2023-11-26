#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>

#include "../include/constants.hpp"
#include "../include/objects.hpp"
#include "../include/move.hpp"
#include "../include/alglin.hpp"

bool window_is_open = false;
bool game_over = false;

std::mutex move_mutex;

void bot_thread(void *bots_ptr, void *index, void *window_is_open, void* game_over)
{
    std::vector<sf::CircleShape> *bots = (std::vector<sf::CircleShape> *)bots_ptr;
    int *idx = (int *)index;
    bool *open = (bool *)window_is_open;
    bool *go = (bool *)game_over;

    sf::Vector2f dir = random_direction();

    while (*open && !*go)
    {
        move_mutex.lock();
        move_bot(*bots, *idx, dir, *go);
        move_mutex.unlock();
        usleep(1000);
    }
}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Jogo");
    window_is_open = true;

    std::vector<sf::CircleShape> objects;
    create_objects(objects);

    int bot1 = 0;
    int bot2 = 1;
    int bot3 = 2;
    int bot4 = 3;
    std::thread thread1(bot_thread, &objects, &bot1, &window_is_open, &game_over);
    std::thread thread2(bot_thread, &objects, &bot2, &window_is_open, &game_over);
    std::thread thread3(bot_thread, &objects, &bot3, &window_is_open, &game_over);
    std::thread thread4(bot_thread, &objects, &bot4, &window_is_open, &game_over);

    sf::Event event;
    while (window.isOpen() && !game_over)
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

        window.clear();
        draw_objects(window, objects);
        window.display();
    }

    window_is_open = false;

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}
