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
