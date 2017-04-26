////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game 
//Homework: # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the cs_maze class. It contains every
//function. The comments in the file will descripe the functionalty step by step
//to ensure the grader's understanding of all the functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//The cs maze class have ton of algorithm to make the game more interesting. The 
//maze class has a table of vertecis and an array of ints start and end. In the 
//interface the players get passed inside of inside of maze, and from there the 
//player can move inside the maze. Since the player has a pointer to location 
//we dont have to looop through the entire maze to pind a player to display their
//possiable paths. As for generating the map, I have come up with algorithms 
//that set the exact number of paths and numbers of blocks. Each time the game is 
//played the map will be in different size and randomely assighned paths. It will be
//difficult to have to exact map in just few runs. I have made it very random.
//
///////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//CS_Maze -HAS A-> Vertex / Checkpoint
///////////////////////////////////////////////////////////////////////////////
#include "cs_maze.h"
using namespace std;
//Default constructor
//step 1: set size with random 
//step 2: create vertex table with size 
//step 3: allocate int array 
//step 4: call generate map 
//step 5: call read 
//step 6: set start_send 
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
//copy constuctor
//step 1: set size with random 
//step 2: create vertex table with size 
//step 3: set members size in each vertex
//step 4: allocate int array 
//step 5: call generate map 
//step 6: call read 
//step 7: set start_send 
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
//copy constuctor
//step 1: set size to co copy size  
//step 2: create vertex table with size 
//step 3: allocate int array 
//step 4: set start_send  to copy values
//step 5: for loop - copy all vertecies to current table of vertecis  
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
//step 1: for loop - set each vertex members size to passed in size 
void cs_maze::set_players_size(const int to_set)
{
    for(int i = 0; i < size; ++i)
        table[i].create_table(to_set);
}
//step 1: insert the passed player to start location
//setp 2: update the player location 
void cs_maze::start(player & start)
{
    table[start_end[0]].add_player(start);
    start.update_location(table[start_end[0]]);
}
//step 1: check vertex is empty 
//setp 2: if no - winner and display the player return false
//step 3: return true
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
//step 1: find the player location 
//step 2: move from current vertex to adjecent a.k.a path 
//step 4: call trigger reward - if yes than reward is given to player  
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
//step 1: remove the player from current vertex
//step 2: find a friend's location 
//setp 3: add player to friend's locations
//step 4: call trigger reward - if yes than reward is given to player  
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
                {
                    cout<<"\n\n\33[0;31mYou have accuired a reward!:\33[0m\n";
                    to_move.add_reward((random() % 5));
                }
                added = true;
            }
}
//step 1: remove the player from current vertex
//step 2: find an enemy location 
//setp 3: add player to enemies locations
//step 4: call trigger reward - if yes than reward is given to player  
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
                {
                    cout<<"\n\n\33[0;31mYou have accuired a reward!:\33[0m\n";
                    to_move.add_reward((random() % 5));
                }
                added = true;
            }
}
//step 1:  allocate object of read 
//step 2: open the file
//step 3: check if load is not NULL
//step 4: if not end of file continue looping
//step 5: read to array temp
//step 6: call ganhe name function from reward 
//step 7: loop until end of file
//step 8 : close file 
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
//step 1: generate paths numbers
//step 2: pick a starting point to insert number of paths 
//step 3: find a vertex with 1 adjecent 
//step 4: check if nothing is added yet to minus the starting point
//step 5: check probility to insert paths type depending on probility
//step 6: find other verteices with 0 value to insert add the perant adjecents 
//step 7: repaet until full map full connectioms
//step 8: connect cyslical vertices  
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
//step 1: randomize a number of 3 paths vertecies
//step 2: check if 3 paths vetcies it is zero
//step 3: if yes - randomize a number of 2 paths vertecies - possible 3 or 4
//step 4: check if 3 paths vertcies it equal 1 
//step 5: if yes - randomize a number of 2 paths vertecies - possible 1 or 2
//step 6: algorithm to find the numbers of one paths vertices 
//step 7: calulate the number of blocks in the maze
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
}
//step 1: get passed in number and set all the vertices members class to have a set size number of players
void cs_maze::number_of_players(const int playing)
{
    for(int i = 0; i < size; ++i)
        table[i].create_table(playing);
}
//step 1: set start - end to -1
//step 2: for loop until added == to 2
//step 3: if start == -1 than check vertex I is a block 
//step 4: if yes - set start to i and add one to added;
//step 5: if end == -1 than check vertex J is a block 
//step 6: if yes - set end to j and add one to added;
//step 7: set class int array to the values we got for start and end 
void cs_maze::init_start_end()
{
    int added =0;
    int start = -1, end = -1;
    for(int i = 0, j = (size -1); i < size && added != 2 ; ++i, --j)
    { 
        if(start == -1)
            if(table[i].isBlock())
            {
                start = i;
                ++added;
            }
        if(end == -1)
            if(table[j].isBlock())
            {
                end = j;
                ++added;
            }
    }
    start_end[0] = start;
    start_end[1] = end;

}
//step 1: set found to zero
//step 2: foor loop 
//step 3: check if vertex "I" has the passed player
//step 4: if yes - set found to i 
//step 5: go to vertex found and display vertex connection
void cs_maze::display_chocies(const player & to_find)
{
    int found = 0;
    for(int i = 0; i< size && !found; ++i)
        if(table[i].isMember(to_find))
            found = i;

    table[found].display_connections();
}
//step 1: Display start vertex 
//step 2: display end vertex
//step 3: for loop
//step 4: display vertex's name 
//step 4: display vertex's adjecents  
//step 4: display players in vertex "i"
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
//Destructor 
//step 1: delete table and int array 
cs_maze::~cs_maze()
{
    delete [] table;
    delete [] start_end;
}
