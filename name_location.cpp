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
    return strcmp(_name, to_comp._name);
}
bool name::compare(const char * to_comp) const
{
    return strcmp(_name, to_comp);
}
//LOCATION CLASS
location::location(): location_id(0)
{
}
location::location(char * to_add): name(to_add), location_id(0)
{
}
location::location(const name & to_copy): name(to_copy), location_id(0)
{
}
location::location(char * to_add, int id): name(to_add), location_id(id)
{
}
location::location(const name & to_copy, int id): name(to_copy), location_id(id)
{
}
location::location(const location & to_copy): name(to_copy), location_id(to_copy.location_id){
}
