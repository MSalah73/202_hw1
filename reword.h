////////////////////////////////////////////
//
//
//
//
//
//
///////////////////////////////////////////

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
