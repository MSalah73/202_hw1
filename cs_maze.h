////////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file only contins the cs maze class. I place it alone becouse it has no "IS A" 
//relationship to any of the classes I wrote.
//
//Descriptions:
//
//CS Maze Class
//The CS maze Class is what gets random vertex and connected them together to make a Maze.
//The class has the functionality to move a player, move to a friend or and enemy, and check 
//and if true display the winner in the maze. Inside of the class is set of algorithms that
//generates the map randomized paths paths. without the good sets of algorithms the maze game
//is pointless and it would not be a maze.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//CS_Maze -HAS A-> Vertex / Checkpoint
/////////////////////////////////////////////////////////////////////////////////////////
#include "map_vertex_checkpoint.h"
class cs_maze
{
    public:
        cs_maze();
        cs_maze(const int players_table_size);
        cs_maze(const cs_maze & to_copy);
        ~cs_maze();

        void start(player & start);
        void move_player(player & to_play, int move_to);
        void move_to_friend(player & to_move);
        void move_to_enemy(player & to_move);
        void number_of_players(const int playing);
        void display_chocies(const player & to_find);
        bool check_winner();
        void display_map();

    private:
        void set_players_size(const int to_set);
        void generate_map();
        void generate_paths(int * paths, int blocks); 
        void init_start_end();
        void read();

        vertex_CP * table;
        int * start_end;
        int size;
};
