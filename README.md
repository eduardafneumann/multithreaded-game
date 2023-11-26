# Game with c++ threads

Simple c++ game made for my operating systems course, dealing with threads and semaphores.

## Install the relevant dependencies
The game was tested in Fedora 38 and Ubuntu 22.
### On fedora
`sudo dnf -y install SFML-devel`

### On ubuntu
`sudo apt-get install libsfml-dev`

## Run
To compile and run the program, once being in the root directory, run

`make`

`make run`

## Game rules
This game was inspired by musical chairs. There are three types of entities: chairs (green or red), bots (yellow) and the player (blue).

Each chair is unavailable, indicated by being red, and when is becomes available, indicated by being green, the player must touch it before any other bot to win points. When it's toched, by a pleyer or by a bot, it becomes unavailable again.

When the player touches the bots, they lose 1 point; when they are the first to touch a chair, they win 10 points; and they also win points as time passes, as a survival bonus. There is no end to the game, the objective is to get as many points as possible.

## Threads
Each bot and each chair is its on thread, so there are 8 aditional threads running during the execution of the game, 4 for bots and 4 for chairs. The player behaviour is controlled by the main thread.

## Shared resources
There are 3 information shared by the threads: whether the window is open or not (stored in the boolean variable `window_is_open`), the current score (stored in the integer variable `score`), and the entities position (stored in the entities vector, a c++ standard vector of SFML's CircularShape, `objects`). The last two have mutexes to control access to them, whereas the first one is only ever read by the aditional threads and modified only by the main thread. This modification is done when the game is closed, and before the main thread exits it waits for the aditional ones to finish, so there is no need to control the access for reading done by the aditional threads. Therefore, the current score and the entities positions are critical regions, while the boolean variable is not.

## Mutexes
The `move_mutex` is used to control the reading and writing of the entities position. This is done by the function `move_bot` in the bot threads, by `deal_with_colision` in the chair threads, and by `move_player` in the main thread.

The `score_mutex` is used to control the reading and wirting of the current score. This is done in the bot threads after the call to `move_bot`, wich returns how many points must be added to the score after the bot moved (the collision of a player and a bot is the only point-event detected here, so it's never a positive value). Similarly, in the chair threads, it's done after the call to `deal_with_colision`, wich also returns the points to be added (never a negative value, it detects only whether a player touched an available chair or not). Finally, in the main thread the score is also incremented, as a survival bonus.

