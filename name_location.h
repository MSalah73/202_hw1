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
        void display() const;
        void change_name(char * to_change);
        void set_name(const name & to_set);
        bool compare(const name & to_comp) const; 
        bool compare(const char * to_comp) const; 
    protected:
        char * _name;
};
class location: public name
{
    public:
        location();
        location(char * to_add, int id);
        location(const name & to_copy, int id);
        location(char * to_add);
        location(const name & to_copy);
        location(const location & to_copy);
        bool coma

    protected:
        int location_id;
};
