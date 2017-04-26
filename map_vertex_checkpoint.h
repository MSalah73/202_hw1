////////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file manges Vertex / Checkpoint class and the DLL Class. These two class are the
//heart of the maze game. The game wound not be functional without them. The vertex
//class is the largest class in the program. However, there are mutiple functions 
//which are not used in the game. There are only used while debugging. I tried to murge 
//these two classes to reduce the amount of functions and to get rid of the setters and
//getters. But, My effeot were in vain. It was really hard becouse of the odd connections
//between the vertex / chickpoint and the DLL. Those two classes has a a "HAS A" relationship
//with each other. I wasted alot of time trying to murging it, but time of the essence. I had 
//stop and restore back my previous implentaion of the classes.
//
//Descriptions:
//
//Vertex/Chickpoint Class:
//The Vertex / Chickpoint class is crutial in this program. The class has many important
//functionality to the game to be dedcuted. The class is a name and members. The vertex 
//class can store player and relseing player to move to vertex's connection with its 
//adjecents. The class alos acn trigger a reward for the value to receive.
//
//DLL Class
//The class is basicliy an adjecent to the vertex class. I tried to copy the stcture 
//from my previous homework in CS 163. The class is a continer of adjecents to a vertex
//and it's a DLL type.
//
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//DLL -HAS A-> Vertex/Chickpoint -HAS A-> DLL
//Vertex/Chickpoint -IS A-> Name
/////////////////////////////////////////////////////////////////////////////////////////
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
