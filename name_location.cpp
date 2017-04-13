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
name::name(char * to_add): _name(NULL)
{
    change_name(to_add);
}
name::name(const name & to_copy): _name(NULL)
{
    set_name(to_copy);
}
void name::change_name(char * to_change)
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
//team CLASS
team::team(): teammates(NULL), team_size(0)
{
}
team::team(char * to_add): name(to_add), teammates(NULL), team_size(0)
{
}
team::team(char * to_add, int num_of_players): name(to_add), teammates(NULL), team_size(0)
{
    create_array(num_of_players);
}
team::team(const name & to_copy, int num_of_players): name(to_copy), teammates(NULL), team_size(0)
{
    create_array(num_of_players);
}
team::team(const team & to_copy): name(to_copy), teammates(NULL), team_size(0)
{
    create_array(to_copy.team_size);
    for(int i = 0; i < team_size; ++i)
        teammates[i] = to_copy.teammates[i];
}
void team::create_array(int size)
{
    team_size = size;
    teammates = new player * [size];
    for(int i = 0; i < size; ++i)
        teammates[i] = NULL;
}
void team::display_team() const
{
    cout<<"Team members:\n";
    for(int i = 0; i < team_size; ++i)
        if(teammates[i])
            teammates[i]->display();
}
void team::add_player(class player & to_add)
{
    bool added = isTeammate(to_add);
    for(int i = 0; i < team_size && !added; ++i)
        if(!teammates[i])
        {
            teammates[i] = &to_add;
            added = true;
        }
}
void team::remove_teammate(const class player & to_remove)
{
    if(!isTeammate(to_remove))
        return;
    bool removed = false;
    for(int i = 0; i < team_size && !removed; ++i)
        if(teammates[i] && teammates[i]->compare(to_remove))
        {
            teammates[i] = NULL;
            removed = true;
        }
}
void team::display_team_locations() const
{
    //after checkpoint - player
}
bool team::isTeammate(const class player & to_comp) const
{
    bool found = false;
    for(int i = 0; i < team_size && !found; ++i)
    {
        if(!teammates[i])
            continue;
        else 
            found = teammates[i] == &to_comp;
    }
    return found;
}
team::~team()
{
    delete [] teammates;
    teammates = NULL;
}
//Player class
player::player()
{
}
player::player( char * to_add): team(to_add)
{
}
player::~player()
{
}
