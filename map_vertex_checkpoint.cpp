///////////////////////////////////////////
//
//
//
//
//
//////////////////////////////////////////
#include "map_vertex_checkpoint.h"
using namespace std;
//VERTEX / vertex_CP CLASS
vertex_CP::vertex_CP(): head(NULL)
{
}
vertex_CP::vertex_CP(const name & to_add, const int size): members(to_add, size), head(NULL)
{
}
vertex_CP::vertex_CP(const members & to_copy): members(to_copy), head(NULL)
{
}
vertex_CP::vertex_CP(const vertex_CP & to_copy): members(to_copy), head(NULL)
{
    copy_DLL(to_copy.head, head, NULL);
}
void vertex_CP::copy(const vertex_CP & to_copy)
{
    set_name(to_copy);
    copy_members(to_copy);
    copy_DLL(to_copy.head, head, NULL);
}
void vertex_CP::add_path(vertex_CP & to_add)
{
    add_path(to_add, head);
}
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
void vertex_CP::move_player(player & to_move, int move_to)
{
    if(!head)
        return;
    move_player(to_move, move_to, head);
    remove_player(to_move);
}
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
void vertex_CP::move_player(player & to_move, const vertex_CP & move_to)
{
    if(!head)
        return;
    remove_player(to_move);
    move_player(to_move, move_to, head);
}
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
void vertex_CP::display_connections() const
{
    display_connections(head, 1);
}

bool vertex_CP::isValid_path(int valid) const
{
    if(!head || valid < 0)
        return false;
    return isValid_path(valid, head);
}
bool vertex_CP::isValid_path(int valid, DLL_node * path) const
{
    if(!path)
        return false;
    if(!valid)
        return true;
    --valid;
    return isValid_path(valid, path->go_next());
}
void vertex_CP::display_connections(DLL_node * to_display, int counter) const
{
    if(!to_display)
        return;
    cout<<counter<<" - ";
    to_display->display();
    ++counter;
    display_connections(to_display->go_next(),counter);

}
void vertex_CP::display_prev(DLL_node * to_display) const
{
    if(!to_display)
        return;
    display_prev(to_display->go_previous());
    to_display->display();
}
void vertex_CP::copy_DLL(DLL_node * src, DLL_node *& dest,  DLL_node * prev)
{
    if(!src)
        return;
    dest = new DLL_node(*src);
    if(prev)
        dest->go_previous() = prev;
    copy_DLL(src->go_next(), dest->go_next(), dest);
}
bool vertex_CP::trigger_reward() const
{
    if(random() % 3)
        return true;
    return false;
}
bool vertex_CP::isBlock()
{
    if(!head)
        return false;
    if(!head->go_next())
        return true;
    return false;
}
void vertex_CP::delete_node(const vertex_CP & to_delete)
{
    delete_node(to_delete, head);
}
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
void vertex_CP::destroy()
{
    destroy(head);
}
void vertex_CP::destroy(DLL_node *& to_destroy)
{
    if(!to_destroy)
        return;
    destroy(to_destroy->go_next());

    delete to_destroy;
}
vertex_CP::~vertex_CP()
{
    destroy(head);
}
//DLL_NODE class
DLL_node::DLL_node(): next(NULL), previous(NULL), adjecent(NULL)
{
}
DLL_node::DLL_node(vertex_CP & to_copy): next(NULL), previous(NULL), adjecent(NULL)
{
    adjecent = &to_copy;
}
DLL_node::DLL_node(const DLL_node & to_copy): next(NULL), previous(NULL), adjecent(NULL)
{
    adjecent = to_copy.adjecent;
}
DLL_node *& DLL_node::go_next()
{
    return this->next;
}
DLL_node *& DLL_node::go_previous()
{
    return this->previous;
}
void DLL_node::connect_next(DLL_node * to_connect)
{
    this->next = to_connect;
}
void DLL_node::connect_previous(DLL_node * to_connect)
{
    this->previous = to_connect;
}
void DLL_node::display()
{
    if(!adjecent)
        return;
    adjecent->display();
}
bool DLL_node::compare_adj(const vertex_CP & to_comp)
{
    return to_comp.compare(*adjecent);
}
void DLL_node::add_player(player & to_add)
{
    adjecent->add_player(to_add);
    to_add.update_location(*adjecent);
}
DLL_node::~DLL_node()
{
    previous = next = NULL;
    adjecent = NULL;
}
