//////////////////////////////////
//
//
//
//////////////////////////////////
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
