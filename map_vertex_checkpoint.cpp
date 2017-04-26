////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game 
//Homework: # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////
//This file contains the implentaion of the vertex/Chickpoint and the DLL
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
//The vertex/Chickpoint is a core of the game. It's from the maze. Each vertex
//act indendently from other ones. Each vertex has a storage of players depending
//on the people playing the game. I have set selected a limited  set of 3 number 
//of players for the user to pick. This ensure that the game is enjoyed without
//the user breaking the game with slecting huge number of players. The player
//can only move from the current vertex to the adjecents vertexes connected to it.
//
///////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//DLL -HAS A-> Vertex/Chickpoint -HAS A-> DLL
//Vertex/Chickpoint -IS A-> Name
///////////////////////////////////////////////////////////////////////////////
#include "map_vertex_checkpoint.h"
using namespace std;
//Vertex / Checkpoint - a.k.a vertex_CP CLASS
//Default constructor
vertex_CP::vertex_CP(): head(NULL)
{
}
//Copy constructor
vertex_CP::vertex_CP(const name & to_add, const int size): members(to_add, size), head(NULL)
{
}
//Copy constructor
vertex_CP::vertex_CP(const members & to_copy): members(to_copy), head(NULL)
{
}
//Copy constructor
//step 1: call copy_DLL to proform copy from passed object recurcivliy
vertex_CP::vertex_CP(const vertex_CP & to_copy): members(to_copy), head(NULL)
{
    copy_DLL(to_copy.head, head, NULL);
}
//Step 1: call set name and and pass object to copy name 
//Step 2: call copy_members to copy all players from passed object
//step 3: call copy_DLL to proform copy from passed object recurcivliy
void vertex_CP::copy(const vertex_CP & to_copy)
{
    set_name(to_copy);
    copy_members(to_copy);
    copy_DLL(to_copy.head, head, NULL);
}
//wrapper
//step 1: call add_path with head pointer
void vertex_CP::add_path(vertex_CP & to_add)
{
    add_path(to_add, head);
}
//step 1: allcoate with new and pass in vertex object to copy
//step 2: check if current head is NULL
//step 3: if yes - set head to temp
//step 4: if no - temp' next pointer points to head 
//step 5: call head to_connect to connect to temp 
//step 3: set head to temp
void vertex_CP::add_path(vertex_CP & to_add, DLL_node *& to_set)
{
    DLL_node * temp = new DLL_node(to_add);
    if(!to_set)
        to_set = temp;
    else
    {
        temp->go_next() = to_set;
        to_set->connect_previous(temp);
        to_set = temp;
    }
}
//step 1: check if head is NULL
//step 2: if yes - return
//step 3: call recursive verion of the function with head pinter
//step 4: remove the player from the current vertex
void vertex_CP::move_player(player & to_move, int move_to)
{
    if(!head)
        return;
    move_player(to_move, move_to, head);
    remove_player(to_move);
}
//step 1: check if head is NULL
//step 2: if yes - return
//step 3: check if found is true/false
//step 4: if yes - move the play to the vertex and return 
//step 5: minus the found by one
//step 6: call recursive verion of the function with next pinter
void vertex_CP::move_player(player & to_move, int found, DLL_node *& move_to)
{
    if(!move_to)
        return;
    if(!found)
    {
        move_to->add_player(to_move);
        return;
    }
    --found;
    move_player(to_move, found, move_to->go_next());
}
//step 1: check if head is NULL
//step 2: if yes - return
//step 3: call recursive verion of the function with head pinter
//step 4: remove the player from the current vertex
void vertex_CP::move_player(player & to_move, const vertex_CP & move_to)
{
    if(!head)
        return;
    remove_player(to_move);
    move_player(to_move, move_to, head);
}
//step 1: check if head is NULL
//step 2: if yes - return
//step 3: check if compare adjecent is true/false
//step 4: if yes - move the play to the vertex and return 
//step 6: call recursive verion of the function with next pinter
void vertex_CP::move_player(player & to_move, const vertex_CP & to_comp, DLL_node *& move_to)
{
    if(!move_to)
        return;
    if(move_to->compare_adj(to_comp))
    {
        move_to->add_player(to_move);
        return;
    }
    move_player(to_move, to_comp, move_to->go_next());
}
//step 1: call recursive version of display connections with head pointer 
//NOTE  the passed 1 is for counter - to display in numrical order
void vertex_CP::display_connections() const
{
    display_connections(head, 1);
}
//step 1: check if head is NULL or the value is less than zero
//step 2; if yes - return
//step 3: call recursive verion with head pointer 
bool vertex_CP::isValid_path(int valid) const
{
    if(!head || valid < 0)
        return false;
    return isValid_path(valid, head);
}
//step 1: check if head is null
//step 2: if yes - return false 
//step 3: check if the passed value is zero
//step 4: if yes - return true 
//step 5: minus the value by one
//step 6: call it self with next pointer
bool vertex_CP::isValid_path(int valid, DLL_node * path) const
{
    if(!path)
        return false;
    if(!valid)
        return true;
    --valid;
    return isValid_path(valid, path->go_next());
}
//step 1: check if head is null
//step 2: display the path's name
//step 3: call it self with the next pointer
void vertex_CP::display_connections(DLL_node * to_display, int counter) const
{
    if(!to_display)
        return;
    cout<<counter<<" - ";
    to_display->display();
    ++counter;
    display_connections(to_display->go_next(),counter);

}
//step 1: check if head is null
//step 2: if yes - return
//step 3: call it self recursively with previous pointer
//step 4: display adjecent's names
void vertex_CP::display_prev(DLL_node * to_display) const
{
    if(!to_display)
        return;
    display_prev(to_display->go_previous());
    to_display->display();
}
//step 1: check if head is null
//step 2: if yes - return
//step 3: allocate dest with new and the address of src to copy from sorce by calling the copy constructor
//step 4: check if prev is null
//step 5: if yes - set dest previous to the previous pointer
//step 6: call it self recursivliy with the next pointers
void vertex_CP::copy_DLL(DLL_node * src, DLL_node *& dest,  DLL_node * prev)
{
    if(!src)
        return;
    dest = new DLL_node(*src);
    if(prev)
        dest->go_previous() = prev;
    copy_DLL(src->go_next(), dest->go_next(), dest);
}
//step 1: randomly pick a value from 0 to 2
//step 2: if true - return true
//step 3:  return false 
bool vertex_CP::trigger_reward() const
{
    if(random() % 3)
        return true;
    return false;
}
//step 1: check if head is null
//step 2: if yes - return false 
//step 3: check if head next is null
//step 4: if yes - return true 
//step 5: return false 
bool vertex_CP::isBlock()
{
    if(!head)
        return false;
    if(!head->go_next())
        return true;
    return false;
}
//wrapper
//step 1: call recursive verion it it self with head pointer
void vertex_CP::delete_node(const vertex_CP & to_delete)
{
    delete_node(to_delete, head);
}
//step 1: check if head is null
//step 2: if yes - return
//step 3: check if current is the same as the passed vertex
//step 4: if yes - set nopinters 
//step 4a: check if previous is null 
//step 4b current set to next
//step 5: else - previous conneect its next to next and vise versa
//step 6: dlete hold and return
//step 7 : step 3 if not equal than call it self recursivliy with the next pointer
void vertex_CP::delete_node(const vertex_CP & to_comp, DLL_node *& to_delete)
{
    if(!to_delete)
        return;
    if(to_delete->compare_adj(to_comp))
    {
        DLL_node * hold = to_delete,
             * previous = to_delete->go_previous(),
             * next = to_delete->go_next();
        if(!previous)
            to_delete = next;
        else
        {
            previous->connect_next(next);
            next->connect_previous(previous);
        }
        delete hold;
        return;
    }
    delete_node(to_comp, to_delete->go_next());
}
//wrapper
//step 1: call recursive verion of it self with head pointer
void vertex_CP::destroy()
{
    destroy(head);
}

//step 1: check if head is null
//step 2: if yes - return
//step 3: call it self with next pointer 
//step 4: delete head;
void vertex_CP::destroy(DLL_node *& to_destroy)
{
    if(!to_destroy)
        return;
    destroy(to_destroy->go_next());

    delete to_destroy;
}
//Destructor 
//Call destory with head pointer
vertex_CP::~vertex_CP()
{
    destroy(head);
}
//DLL_NODE class
//Default constructor
DLL_node::DLL_node(): next(NULL), previous(NULL), adjecent(NULL)
{
}
//Copy constructor
//step 1: set adjecent pointer to the address of to_copy of tyoe vertex
DLL_node::DLL_node(vertex_CP & to_copy): next(NULL), previous(NULL), adjecent(NULL)
{
    adjecent = &to_copy;
}
//Copy constructor
//step 1: set adjecent pointer to to_copy of tyoe vertex's pointer
DLL_node::DLL_node(const DLL_node & to_copy): next(NULL), previous(NULL), adjecent(NULL)
{
    adjecent = to_copy.adjecent;
}
//step 1: return next pointer
DLL_node *& DLL_node::go_next()
{
    return this->next;
}
//step 1: return previous pointer
DLL_node *& DLL_node::go_previous()
{
    return this->previous;
}
//setp 1: connect this' next to to_connect;
void DLL_node::connect_next(DLL_node * to_connect)
{
    this->next = to_connect;
}
//setp 1: connect this' previous to to_connect;
void DLL_node::connect_previous(DLL_node * to_connect)
{
    this->previous = to_connect;
}
//step 1: check if adjecent is null
//step 2: display vertex's name
void DLL_node::display()
{
    if(!adjecent)
        return;
    adjecent->display();
}
//step 1: return a true or false depening if the current vertex is equal to the passed in vertex
bool DLL_node::compare_adj(const vertex_CP & to_comp)
{
    return to_comp.compare(*adjecent);
}
//step 1: added the player to the vertex
//step 2: update players location by passing the address of vertex
void DLL_node::add_player(player & to_add)
{
    adjecent->add_player(to_add);
    to_add.update_location(*adjecent);
}
//Destrcutor
//step 1: step all pointer to NULL
DLL_node::~DLL_node()
{
    previous = next = NULL;
    adjecent = NULL;
}
