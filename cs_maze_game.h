///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file manges cs_maze_game class. Each class has a
//Porpuse and they have their own "Job" in the program. The OOP design 
//sumulates the connections from paper to actual program. 
//
//Descriptions:
//
//CS Maze Game Class
//This class is the manger that connect all the classes and fuctions together to make the game 
//playable. The class is basicaily the interface of the whole program. Its not a beatifully
//made interface but it does what it need to be done. 
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//CS Maze Game -HAS A-> CS Maze
//CS Maze Game -HAS A-> Player
/////////////////////////////////////////////////////////////////////////////////////////
#include "cs_maze.h"
class cs_maze_game
{
    public:
        cs_maze_game();
        cs_maze_game(const cs_maze_game & to_copy);
        ~cs_maze_game();
        void start();

    private:
        bool menu(int Turn);
        void set_tables();
        void set_teams();
        int display_options(int Turn);
        bool reward_menu(int Turn);
        bool turn(player & to_play);
        void activate_reward(const int use, int Turn);

        cs_maze * maze;
        player * players_table;
        int table_size;
};
