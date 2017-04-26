//////////////////////////////////////////
//
//
//
//
//
//
/////////////////////////////////////////
#include "reword.h"
using namespace std;
reward::reward(): rewards(NULL), next(NULL), activation_table(NULL) 
{
    activation_table = new bool[5];
    rewards = new name[5];
    for(int i = 0; i < 5 ; ++i)
        activation_table[i] = false;
    read();
}
reward::reward(const reward & to_copy): rewards(NULL), next(NULL), activation_table(NULL) 
{
    activation_table = new bool[5];
    rewards = new name[5];
    for(int i = 0; i < 5 ; ++i)
    {
        activation_table[i] = to_copy.activation_table[i];
        rewards[i].set_name(to_copy.rewards[i]);
    }
    copy(&to_copy, next);
}
void reward::copy(const reward * src, reward *& dest)
{
    if(!src)
        return;
    dest = new reward(*src);
}
void reward::read()
{
    ifstream load;
    char array[100];
    int counter(0);
    load.open("reward.txt");
    if(load)
    {
        while(!load.eof())
        {
            load.get(array,100,'\n');
            load.ignore(100,'\n');
            if(!load.eof())
                rewards[counter].change_name(array);
            ++counter;
        }
    }
    load.clear();
    load.close();
}
void reward::activate_reward(const int to_activate)
{
    if(to_activate > 5)
        return;
    if(!activation_table[to_activate])
        activation_table[to_activate] = true;
    else
        activate_reward(to_activate, next);
   rewards[to_activate].display(); 
}
void reward::activate_reward(const int to_activate, reward *& head)
{
    if(!head)
        head = new reward;
    if(!head->activation_table[to_activate])
    {
        head->activation_table[to_activate] = true;
        return;
    }
    activate_reward(to_activate, head->next);
}
bool reward::use_reward(const int use)
{
    if(use > 5)
        return false;
    if(!activation_table[use])
        return use_reward(next, use);
    else
        return !(activation_table[use] = false);
}
bool reward::use_reward(reward *& to_check, const int use)
{
    if(!to_check)
        return false;
    if(to_check->activation_table[use])
    {
        to_check->activation_table[use] = false;
        return true;
    }
   return use_reward(to_check->next, use);
}
void reward::display()
{
    int num_acti[5];
    for(int i = 0; i < 5; ++i)
        num_acti[i] = 0;
    display(this, num_acti);
    
    for(int i = 0; i < 5; ++i)
    {
        cout<<i+1<<" - ";
        rewards[i].display();
        cout<<"# "<<num_acti[i]<<endl;
    }
}
void reward::display(const reward * to_check, int * to_display)
{
    if(!to_check)
        return;
    for(int i = 0; i < 5; ++i)
        if(to_check->activation_table[i])
            ++to_display[i]; 
    display(to_check->next, to_display);
}
void reward::destroy(reward *& head)
{
    if(!head)
        return;
    destroy(head->next);
    delete head;
    head = NULL;
}
reward::~reward()
{
    destroy(next);
    delete [] rewards;
    delete [] activation_table; 
    activation_table = NULL;
    rewards = NULL;
}

