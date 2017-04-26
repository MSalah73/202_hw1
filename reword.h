///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//This file only contins the reward. I have manged to merge Reward and Linear Linked List
//In one class. It was diffeclt at first but I manged to impelented with out m emory leaks
//
//Descriptions:
//
//Reward Class:
//This class contains the list of reward in forms of names. The class is a List of reward.
//The class manages all the reward gevein to a player. The reward class is give the games 
//a little flare. Nothing more boring than a game without spicail item to use to slow other
//team members. Some items can make the game easier. In my opinion, this class is very 
//important as it given the game spicail pearks.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//Reward -HAS A-> Name
/////////////////////////////////////////////////////////////////////////////////////////
#include "name_location.h"
#ifndef REWORD_H
#define REWORD_H
class reward
{
    public:
        reward();
        reward(const reward & to_copy);
        ~reward();

        void activate_reward(const int to_activate);
        bool use_reward(const int use);
        void display();

    private:
        void read();
        void copy(const reward * src, reward *& dest);
        void activate_reward(const int to_activate, reward *& head);
        void display(const reward * to_check, int * to_display);
        bool use_reward(reward *& to_check, const int use);
        void destroy(reward *& head);

        name * rewards;
        reward * next;
        bool * activation_table;
};
#endif
