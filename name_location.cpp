////////////////////////////////
//
//
//
//
//
///////////////////////////////

#include "name_location.h"
using namespace std;
//NAME CLASS
name::name(): _name(NULL)
{
}
name::name(const char * to_add): _name(NULL)
{
    change_name(to_add);
}
name::name(const name & to_copy): _name(NULL)
{
    set_name(to_copy);
}
void name::change_name(const char * to_change)
{
    if(!to_change)
        return;
    if(_name)
        delete [] _name;
    _name = new char[strlen(to_change)+1];
    strcpy(_name, to_change);
}
void name::display() const
{
    cout<<"Name: "<<_name<<endl;
}
void name::set_name(const name & to_set)
{
    if(to_set._name)
        change_name(to_set._name);
}
bool name::compare(const name & to_comp) const
{
    return !strcmp(_name, to_comp._name);
}
bool name::compare(const char * to_comp) const
{
    return !strcmp(_name, to_comp);
}
name::~name()
{
    delete [] _name;
    _name = NULL;
}
//members CLASS
members::members():player_table(NULL), size(0)
{
}
members::members(const char * to_add): name(to_add), player_table(NULL), size(0)
{
}
members::members(const char * to_add, const int to_size): name(to_add), player_table(NULL), size(0)
{
    create_table(to_size);
}
members::members(const name & to_copy, const int to_size): name(to_copy), player_table(NULL), size(0)
{
    create_table(to_size);
}
members::members(const members & to_copy): name(to_copy), player_table(NULL), size(0)
{
    copy_members(to_copy);
}
void members::copy_members(const members & to_copy)
{
    create_table(to_copy.size);
    for(int i = 0; i < size; ++i)
        player_table[i] = to_copy.player_table[i];
}
void members::create_table(const int to_size)
{
    size = to_size;
    player_table = new player * [size];
    for(int i = 0; i < size; ++i)
        player_table[i] = NULL;
}
void members::display_players() const
{

    cout<<"\33[0;31m-----friend's name-----\33[0m\n";
    for(int i = 0; i < size; ++i)
        if(player_table[i])
            player_table[i]->display();
}
void members::add_player(class player & to_add)
{
    bool added = isMember(to_add);
    for(int i = 0; i < size && !added; ++i)
        if(!player_table[i])
        {
            player_table[i] = &to_add;
            added = true;
        }
}
void members::remove_player(const class player & to_remove)
{
    if(!isMember(to_remove))
        return;
    bool removed = false;
    for(int i = 0; i < size && !removed; ++i)
        if(player_table[i] && player_table[i]->compare(to_remove))
        {
            player_table[i] = NULL;
            removed = true;
        }
}
void members::display_players_locations() const
{
    cout<<"\33[0;31m-----Player's name-----\33[0m\n";
    for(int i = 0; i < size; ++i)
        if(player_table[i])
        {
            player_table[i]->display();
            player_table[i]->display_location();
            cout<<"\33[0;31m-----------------------\33[0m\n";
        }
}
bool members::isMember(const class player & to_comp) const
{
    bool found = false;
    for(int i = 0; i < size && !found; ++i)
    {
        if(!player_table[i])
            continue;
        else 
            found = player_table[i] == &to_comp;
    }
    return found;
}
bool members::isEmpty() const
{
    bool found = true;
    for(int i = 0; i < size && found; ++i)
        if(player_table[i])
            found = false;
    return found;
}
bool members::isFriend(const class player & to_compare)const
{
    bool found = false;
    for(int i = 0; i < size && !found; ++i)
        if(player_table[i])
            if(player_table[i]->isMember(to_compare))
                found = true;
    return found;
}
members::~members()
{
    delete [] player_table;
    player_table = NULL;
}
//Player class
player::player():location(NULL), paralyze(false)
{
    reward_inventory = new reward;
}
player::player(char * to_add, const int team_size): members(to_add, team_size), location(NULL),paralyze(false)
{
    reward_inventory = new reward;
}
player::player(const player & to_copy): location(NULL)
{
    paralyze = to_copy.paralyze;
    reward_inventory = new reward(*to_copy.reward_inventory);
    location = to_copy.location;
}
bool player::isParalyzed()
{
    if(paralyze)
        return true;
    return false;
}
void player::change_effect()
{
    paralyze = !paralyze;
}
void player::add_reward(const int to_activate)
{
    reward_inventory->activate_reward(to_activate);
}
bool player::use_reward(const int use)
{
    return reward_inventory->use_reward(use);
}
void player::update_location(vertex_CP & to_update)
{
    location = &to_update;
}
void player::display_rewards() const
{
    reward_inventory->display();
}
void player::display_info() const
{
    cout<<"\n\33[0;31m-----Player's infromation-----\33[0m\n";
    display();
    cout<<"\33[0;31m-----Rewards inventory-----\33[0m\n";
    reward_inventory->display();
    if(location)
    {
        display_location();
        cout<<"\n\33[0;31m-----Possible paths to take-----\33[0m\n";
        location->display_connections();
    }
    cout<<"\33[0;31m-----Friends locations-----\33[0m\n";
    display_players_locations();
}
void player::display_location() const
{
    if(!location)
        return;
    cout<<"\33[0;31m-----Current Location-----\33[0m\n";
    location->display();
}
void player::display_paths() const
{
    location->display_connections();
}
bool player::isValid_path(int valid)const 
{
    if(!location)
        return true;
    return location->isValid_path(valid);
}
player::~player()
{
    delete reward_inventory;
    location = NULL;
}
