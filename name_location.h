///////////////////////////////////////
//
//
//
//
//
//
//////////////////////////////////////
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#ifndef NAME_LOCATION_H
#define NAME_LOCATION_H
//Try to replace setter fuction drived classes should takle care of compare and stuff. name is fin tho
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
        void display_players() const; //merge displays
        void add_player(class player & to_add);
        void display_players_locations() const;// After vertex - player ///change
        bool isMember(const class player & to_comp) const;//do as a virtual display
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
