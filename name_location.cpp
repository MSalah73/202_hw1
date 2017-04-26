///////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game 
//Homework: # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the name, memebrs, and player
//classes. It contains every function. The comments in the file will descripe
//the functionalty step by step to ensure the grader's understanding of all 
//the functions.
//
//As I immplented all of the classes, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//As the players in the game is initailized, The player's initializetion list 
//classs the name constructor than the members constuctor and lastly the player's
//constructor. Since in the cs_maze_game class it initailaize all the players as
//an array the player defalut constuctor will be called. so, I had to implement 
//some fuction to set the size of the team memebers for exapmle. However, the 
//copy constoctor will come in hadny when intailuzing players indviualy.
//
///////////////////////////////////////////////////////////////////////////////
////Hierarchy Connections:
//Player -IS A-> Member -IS A-> Name
///////////////////////////////////////////////////////////////////////////////

#include "name_location.h"
using namespace std;
//NAME CLASS
//Default constructor
name::name(): _name(NULL)
{
}
//Copy constuctor
//Step 1: Call name's change name function
//and pass the const char as an arguments.
name::name(const char * to_add): _name(NULL)
{
    change_name(to_add);
}
//Copy constuctor
//Step 1: Call name's set name function
//and pass the const object of name as an arguments.
name::name(const name & to_copy): _name(NULL)
{
    set_name(to_copy);
}
//This fuction will change the name of current object' name 
//to the passed in char.
//Step 1: check if the passed in value is NULL
//Step 2: check if name data memeer has data in it
//Step 2a: if so, delete the name data
//Step 3: set current object's name to the size of passed in name
//Step 4:copy the the data from passed in name to the current object's name
void name::change_name(const char * to_change)
{
    if(!to_change)
        return;
    if(_name)
        delete [] _name;
    _name = new char[strlen(to_change)+1];
    strcpy(_name, to_change);
}
//Step 1: display's current object' name
void name::display() const
{
    cout<<"Name: "<<_name<<endl;
}
//Step 1: check if the passed in object of name's name data member is not NULL
//step 2: if not NULL than call change name function
void name::set_name(const name & to_set)
{
    if(to_set._name)
        change_name(to_set._name);
}
//Step 1: return the value from comparing the passed in data with the object data
bool name::compare(const name & to_comp) const
{
    return !strcmp(_name, to_comp._name);
}
//Step 1: return the value from comparing the passed in data with the object data
bool name::compare(const char * to_comp) const
{
    return !strcmp(_name, to_comp);
}
//Destructor
//Step 1: delete array names object 
//Step 2: set it to NULL
name::~name()
{
    delete [] _name;
    _name = NULL;
}
//members CLASS
//Default constructor
members::members():player_table(NULL), size(0)
{
}
//Copy constuctor
//Step 1: call name copy contructor
//step 2: Set data members to NULL
members::members(const char * to_add): name(to_add), player_table(NULL), size(0)
{
}
//Copy constuctor
//Step 1: call name copy contructor
//step 2: Set data members to NULL
members::members(const char * to_add, const int to_size): name(to_add), player_table(NULL), size(0)
{
    create_table(to_size);
}
//Copy constuctor
////Step 1: call name copy contructor
//step 2: Set data members to NULL
//step 3: Create the player table from the passed in argumernt to_size
members::members(const name & to_copy, const int to_size): name(to_copy), player_table(NULL), size(0)
{
    create_table(to_size);
}
//Copy constuctor
////Step 1: call name copy contructor
//step 2: Set data members to NULL
//Step 3: call copy memebers fuction to copy all passed in members object
members::members(const members & to_copy): name(to_copy), player_table(NULL), size(0)
{
    copy_members(to_copy);
}
//Step 1: Call the create player table function and pass the passed in object size
//Step 2: for loop untill it reaches the size 
//Step 3: copy the pointer from to_copy to current objects
void members::copy_members(const members & to_copy)
{
    create_table(to_copy.size);
    for(int i = 0; i < size; ++i)
        player_table[i] = to_copy.player_table[i];
}
//Step 1: set the size to passed in value
//Step 2: crate the player pointer table 
//Step 3: for loop until size and set the pointer to NULL
void members::create_table(const int to_size)
{
    size = to_size;
    player_table = new player * [size];
    for(int i = 0; i < size; ++i)
        player_table[i] = NULL;
}
//Step 1: Display cout
//Step 2: for loop untill size
//step 2a: check if player exixt
//Step 2aa: Call names display
void members::display_players() const
{

    cout<<"\33[0;31m-----friend's name-----\33[0m\n";
    for(int i = 0; i < size; ++i)
        if(player_table[i])
            player_table[i]->display();
}
//Step 1: set added to if the passed in object is a memeber
//Step 2: for loop untill size and if added is true
//Step 3: If table has a spot then add the player address
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
//Step 1: check if passed in object is not member 
//step 2: if a member than for loop until found 
//step 3: Delete found player in the table
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
//Step 1: for loop untill size
//Step 2: If player exixt
//Step 3: Display player's name and location
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
//Step 1: for loop until size
//Step 2: if player not NULL 
//Step 3: cpompare the two player addresses and set them to found
//Step 4: return found
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
//Step 1: for loop until size
//Step 2: if player not NULL 
//Step 3: cpompare the two player addresses and set them to found
//Step 4: return found
bool members::isEmpty() const
{
    bool found = true;
    for(int i = 0; i < size && found; ++i)
        if(player_table[i])
            found = false;
    return found;
}
//Step 1: for loop until size
//Step 2: if player not NULL 
//Step 3: if the player is a member in the table - set found to true
//Step 4: return found
bool members::isFriend(const class player & to_compare)const
{
    bool found = false;
    for(int i = 0; i < size && !found; ++i)
        if(player_table[i])
            if(player_table[i]->isMember(to_compare))
                found = true;
    return found;
}
//Class destructor
//step 1: delete table
//step 2: set tale to NULL
members::~members()
{
    delete [] player_table;
    player_table = NULL;
}
//Player class
//Defualt constructor
//step 1: allocate reward list
player::player():location(NULL), paralyze(false)
{
    reward_inventory = new reward;
}
//Copy constructor
//step 1: allocate reward list
player::player(char * to_add, const int team_size): members(to_add, team_size), location(NULL),paralyze(false)
{
    reward_inventory = new reward;
}
//Copy constructor
//step 1: set current obkect player status to copy status
//step 2: set and call reward copy constrcutor to set to_copy's rewards in current object reward
//step 3: set current object's location to  to_copy's location
player::player(const player & to_copy): location(NULL)
{
    paralyze = to_copy.paralyze;
    reward_inventory = new reward(*to_copy.reward_inventory);
    location = to_copy.location;
}
//step 1: check is paralyzed tsatues is true
//step 2: return true/false depending on if statment
bool player::isParalyzed()
{
    if(paralyze)
        return true;
    return false;
}
//Step 1: set paralyze to not paralyze 
void player::change_effect()
{
    paralyze = !paralyze;
}
//step 1:  pass in the passed in value to activated in the reward class
void player::add_reward(const int to_activate)
{
    reward_inventory->activate_reward(to_activate);
}
//step 1: pass in the passed value and call the use reward fuction
//step 2: return true if the reward is used - false if not
bool player::use_reward(const int use)
{
    return reward_inventory->use_reward(use);
}
//step 1: set the loaction to a chickponit/vertex address
void player::update_location(vertex_CP & to_update)
{
    location = &to_update;
}
//step 1: call display rewards 
void player::display_rewards() const
{
    reward_inventory->display();
}
//Step 1: call display name from name class
//Step 2: call dispaly rewards from reward class
//Step 3: call display loaction if exixt from name class
//Step 4: call display current location paths if exsist from member class
//Step 5: call display friends locations from member class
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
//step 1: if location exixt - display location
void player::display_location() const
{
    if(!location)
        return;
    cout<<"\33[0;31m-----Current Location-----\33[0m\n";
    location->display();
}
//step 1: call locations's display paths 
void player::display_paths() const
{
    location->display_connections();
}
//Step 1: check if locaion exist
//step 2: return true in not 
//step 3: return true or false depending if the number given is associated with a path 
bool player::isValid_path(int valid)const 
{
    if(!location)
        return true;
    return location->isValid_path(valid);
}
//Destructor
//Step 1: delete reward
//step 2: set location to NULL
player::~player()
{
    delete reward_inventory;
    location = NULL;
}
