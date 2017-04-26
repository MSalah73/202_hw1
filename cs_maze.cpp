///////////////////////////////////////
//
//
//
//
//////////////////////////////////////
#include "cs_maze.h"
using namespace std;
cs_maze::cs_maze()
{
    size = random() % 7;
    size += 14;
    table = new vertex_CP[size];
    start_end = new int[2];
    generate_map();
    read();
    init_start_end();
}
cs_maze::cs_maze(const int players_table_size)
{
    size = random() % 7;
    size += 14;
    table = new vertex_CP[size];
    set_players_size(players_table_size);
    start_end = new int[2];
    generate_map();
    read();
    init_start_end();
}
cs_maze::cs_maze(const cs_maze & to_copy)
{
    size = to_copy.size;
    table = new vertex_CP[size];
    start_end = new int[2];
    start_end[0] = to_copy.start_end[0];
    start_end[1] = to_copy.start_end[1];
    for(int i = 0; i < size; ++i)
        table[i].copy(to_copy.table[i]);
}
void cs_maze::set_players_size(const int to_set)
{
    for(int i = 0; i < size; ++i)
        table[i].create_table(to_set);
}
void cs_maze::start(player & start)
{
    table[start_end[0]].add_player(start);
    start.update_location(table[start_end[0]]);
}
bool cs_maze::check_winner()
{
    if(!table[start_end[1]].isEmpty())
    {
        cout<<"\n\33[0;31m--------WINNER--------\33[0m\n";
        table[start_end[1]].display_players();
        cout<<"\n\33[0;31m--------THANK YOU FOR PLAYING!--------\33[0m\n";
        cout<<"\n--------GOOD BYE / FIN--------\n";
    }
    return !table[start_end[1]].isEmpty();
}
void cs_maze::move_player(player & to_play, int move_to)
{
    bool added = false;
    for(int i = 0; i < size && !added; ++i)
        if(table[i].isMember(to_play))
        {
            table[i].move_player(to_play, move_to); 
            if(table[i].trigger_reward())
            {
                cout<<"\n\n\33[0;31mYou have accuired a reward!:\33[0m\n";
                to_play.add_reward((random() % 5));
            }
            added = true;
        }     
}
void cs_maze::move_to_friend(player & to_move)
{
    bool added = false;
    for(int i = 0; i < size; ++i)
        if(table[i].isMember(to_move))
            table[i].remove_player(to_move);

    for(int i = 0; i < size && !added; ++i)
        if(!table[i].isEmpty())
            if(table[i].isFriend(to_move))
            {
                table[i].add_player(to_move);
                to_move.update_location(table[i]);
                if(table[i].trigger_reward())
                    to_move.add_reward((random() % 5));
                added = true;
            }
}
void cs_maze::move_to_enemy(player & to_move)
{
    bool added = false;
    for(int i = 0; i < size; ++i)
        if(table[i].isMember(to_move))
            table[i].remove_player(to_move);

    for(int i = 0; i < size && !added; ++i)
        if(!table[i].isEmpty())
            if(!table[i].isFriend(to_move))
            {
                table[i].add_player(to_move);
                to_move.update_location(table[i]);
                if(table[i].trigger_reward())
                    to_move.add_reward((random() % 5));
                added = true;
            }

}
void cs_maze::read()
{
    ifstream load;
    char array[100];
    int counter(0);
    load.open("locations.txt");
    if(load)
    {
        while(!load.eof() && counter < size)
        {
            load.get(array,100,'\n');
            load.ignore(100,'\n');
            if(!load.eof())
                table[counter].change_name(array);
            ++counter;
        }
    }
    load.clear();
    load.close();
}
void cs_maze::generate_map()
{
    int paths[3] = {0}, track[size] = {0},
        perant = 0, child = 0, type = 0,
        blocks = 0, all_added = 0, cyclical = 2,
        cyc_one, cyc_two, probility;
    generate_paths(paths, blocks);

    track[random() % size] = 1;
    //this giant do while loop generate the map 
    do
    {
        probility = random() % 101; 
        do
        {
            perant = random() % size;
        }while(track[perant] != 1);

        if(!all_added)
        {
            --track[perant];
            if(paths[2])
                type = 2;
            else
                ++type;
        }
        else if(probility < 85 && (paths[1] || paths[2]))
            do
            {
                type = random() % 2;
                if(cyc_one == perant || cyc_two == perant)
                {
                    if(!paths[1])
                        type = 0;
                }
                else 
                    ++type;
            }while(!paths[type]);
        else
            type = 0;

        --paths[type];
        ++type;
        track[perant] += type;
        all_added += type;

        do
        {
            child = random() % size;
            if(!track[child])
            {
                if(cyclical)
                {
                    if(cyclical == 2)
                        cyc_one = child;
                    else
                        cyc_two = child;
                    --cyclical;
                }
                table[perant].add_path(table[child]);
                table[child].add_path(table[perant]);
                ++track[child];
                --type;
            }
        }while(type);
    }while(all_added < (size - 1));
    //----add a cyclical relasionship----
    table[cyc_one].add_path(table[cyc_two]);
    table[cyc_two].add_path(table[cyc_one]);

}
void cs_maze::generate_paths(int * paths, int blocks)
{
    //----setting three directions paths----
    int III_paths = random() % 3,
        II_paths = 0, num_vertex = 1;

    //----setting two directions paths----
    if(!III_paths)
        II_paths = (random() % 2) + 3;
    else if(III_paths == 1)
        II_paths = (random() % 2) + 1;

    //----setting one direction path----
    for(int i = 0; i < (III_paths); ++i)
        num_vertex += 3;
    for(int i = 0; i < (II_paths); ++i)
        num_vertex += 2;
    paths[0] = size - num_vertex;
    paths[1] = II_paths;
    paths[2] = III_paths;

    //----setting the number of blocks---
    blocks = (num_vertex - (III_paths + II_paths));
    cout<<"\nI"<<paths[0]<<endl
        <<"II"<<paths[1]<<endl
        <<"III"<<paths[2]<<endl
        <<"blacks"<<blocks<<endl;
}
void cs_maze::number_of_players(const int playing)
{
    for(int i = 0; i < size; ++i)
        table[i].create_table(playing);
}
void cs_maze::init_start_end()
{
    int start = -1, end = -1;
    for(int i = 0, j = (size -1); i < size; ++i, --j)
    { 
        if(start == -1)
            if(table[i].isBlock())
                start = i;
        if(end == -1)
            if(table[j].isBlock())
                end = j;
    }
    start_end[0] = start;
    start_end[1] = end;

}
void cs_maze::display_chocies(const player & to_find)
{
    int found = 0;
    for(int i = 0; i< size && !found; ++i)
        if(table[i].isMember(to_find))
            found = i;

    table[found].display_connections();
}
void cs_maze::display_map()
{
    
    cout<<"\n-----start-----\n";
    table[start_end[0]].display();
    cout<<"\n-----end-----\n";
    table[start_end[1]].display();
    for(int i = 0; i< size; ++i)
    {
        cout<<"\n-----node-----\n";
        table[i].display();
        cout<<"\n-----connection-----\n";
        table[i].display_connections();
        cout<<"\n-----members-----\n";
        table[i].display_players();

    }
}
cs_maze::~cs_maze()
{
    delete [] table;
    delete [] start_end;
}
