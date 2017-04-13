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

class name
{
    public:
        name();
        name(char * to_add);
        name(const name & to_copy);
        ~name();

        void display() const;
        void change_name(char * to_change);
        void set_name(const name & to_set);
        bool compare(const name & to_comp) const; 
        bool compare(const char * to_comp) const; 

    protected:
        char * _name;
};
class team: public name// "FRIENDS" class
{
    public:
        team();
        team(char * to_add);
        team(char * to_add, int num_of_players);
        team(const name & to_copy, int num_of_players);
        team(const team & to_copy);
        ~team();

        void create_array(int size);
        void remove_teammate(const class player & to_remove);
        void display_team() const;
        void add_player(class player & to_add);
        void display_team_locations() const;// After checkpoint - player
        bool isTeammate(const class player & to_comp) const;

    protected:
        class player ** teammates;
        int team_size;
};
class player: public team
{
    public:
        player();
        player(char * to_add);
        ~player();
    protected:
  //      List * rewords_head;
  //      checkpoint * location;
};
