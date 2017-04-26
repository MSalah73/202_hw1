////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////
#include "name_location.h"
#ifndef MAP_VERTEX_CHECKPOINT_H
#define MAP_VERTEX_CHECKPOINT_H
class vertex_CP: public members
{
    public:
        vertex_CP();
        vertex_CP(const name & to_add, const int size);
        vertex_CP(const members & to_copy);
        vertex_CP(const vertex_CP & to_copy);
        ~vertex_CP();

        void copy(const vertex_CP & to_copy);
        void delete_node(const vertex_CP & to_delete);
        void destroy();
        void add_path(vertex_CP & to_add);
        void display_connections() const;
        bool trigger_reward() const;// reward - active_reward()
        void move_player(player & to_move, const vertex_CP & move_to);//update player's location 
        void move_player(player & to_move, int move_to);//update player's location 
        bool isBlock();
        bool isValid_path(int valid)const;

    private:
        class DLL_node * head;
        //bool visit_flag;  //maybe??
        
        bool isValid_path(int valid, DLL_node * path) const;
        void move_player(player & to_move,  int found, DLL_node *& move_to);
        void move_player(player & to_move, const vertex_CP & to_comp, DLL_node *& move_to);
        void delete_node(const vertex_CP & to_comp, DLL_node *& to_delete);
        void destroy(DLL_node *& to_destroy);
        void add_path(vertex_CP & to_add, DLL_node *& to_set);
        void copy_DLL(DLL_node * src, DLL_node *& dest, DLL_node * prev);
        void display_connections(DLL_node * to_display, int counter) const;
        void display_prev(DLL_node * to_display) const;

};
class DLL_node
{
    public:
        DLL_node();
        DLL_node(vertex_CP & to_copy);
        DLL_node(const DLL_node & to_copy);
        ~DLL_node();
        
        DLL_node *& go_next();
        DLL_node *& go_previous();
        void connect_next(DLL_node * to_connect);
        void connect_previous(DLL_node *to_connect);
        void display();
        bool compare_adj(const vertex_CP & to_comp);
        void add_player(player & to_add);
    private:
        DLL_node * next;
        DLL_node * previous;
        vertex_CP * adjecent;
};
#endif
