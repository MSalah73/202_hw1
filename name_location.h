///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file manges name, members, and player classes. Each class has a
//Porpuse and they have their own "Job" in the program. The OOP design 
//sumulates the connections from paper to actual program. 
//
//Descriptions:
//
//Name Class:
//The name class is the core of main hub base class of the program. It 
//manages the name of players, chickpoints, and rewards. The class acn be 
//considered as the main core of the program as it is the base class for mainly
//every class.
//
//Members Class
//The member class is a holder of players. Classes like player and a vertex/chickpoint 
//uses this class to store players. In the player class, the members class act as a
//friend holder to store other players in his or her team. While the vertex/checkpoint 
//class store the players that move to it. This class has a substantial imprortance in 
//this OOP program. Without it the game would be functinal.
//
//Player Class
//The player class is also improtant. The class it slef is basicliy a manger of rewards,
//members,and a location. the class sumulate a person in a team that hold rewards and a 
//loaction. The game would not be playable with out this class. 
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//Player -IS A-> Member -IS A-> Name
/////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#ifndef NAME_LOCATION_H
#define NAME_LOCATION_H
class name
{
    public:
        name();
        name(const char * to_add);
        name(const name & to_copy);
        ~name();

        void display() const;
        void change_name(const char * to_change);
        void set_name(const name & to_set);
        bool compare(const name & to_comp) const; 
        bool compare(const char * to_comp) const; 

    protected:
        char * _name;
};
class members: public name// "FRIENDS" class
{
    public:
        members();
        members(const char * to_add);
        members(const char * to_add, const int to_size);
        members(const name & to_copy, const int to_size);
        members(const members & to_copy);
        ~members();

        void create_table(const int to_size);
        void copy_members(const members & to_copy);
        void remove_player(const class player & to_remove);
        void display_players() const; 
        void add_player(class player & to_add);
        void display_players_locations() const;
        bool isMember(const class player & to_comp) const;
        bool isEmpty() const;
        bool isFriend(const class player & to_compare)const;

    protected:
        class player ** player_table;
        int size;
};
#include "reword.h"
#include "map_vertex_checkpoint.h"
class player: public members
{
    public:
        player();
        player(char * to_add, const int team_size);
        player(const player & to_copy);
        ~player();

        bool isParalyzed();
        void change_effect();
        void add_reward(const int to_activate);
        bool use_reward(const int use);
        void display_rewards() const;
        void display_info() const;
        void display_location() const;
        void display_paths() const;
        bool isValid_path(int valid) const;
        void update_location(vertex_CP & to_update);

    private:
        reward * reward_inventory;
        vertex_CP * location;
        bool paralyze;
};
#endif
