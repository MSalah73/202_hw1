///////////////////////////////////////////////////////////////////////////////////////
//Zack Salah
//CS Maze Game
//Homework # 1
//Programming Systems #202
///////////////////////////////////////////////////////////////////////////////////////
//
//This file contains the implentaion of the reward
//only. It contains every function. The comments in the file will descripe
//the functionalty step by step to ensure the grader's understanding of all 
//the functions.
//
//I originlay had two class in this file, reward and List classes. However, I manged 
//murge and get rid of the setters and getters list class. The end reslut is sprisingly 
//good. The amount of code reduced, but alittle hard to imppement. Overall im happy 
//with experimenting murging the node and base classe.
//
//As I immplented all of the class, I have returned and added and fixed some
//of the functions in this file. Becouse most of the function have functions from
//outside of the class. I encourge opening all the files to ensure all of the 
//connections that has been made.
//
//Algorithms
//
//Every player has a reward class. This class help sumelate the players inventory of items.
//The player, this way can store as much items as hee or she can. When the player moves to 
//a new checkpoint / vertex. They may recive a reward from the checkpoint / vertex class 
//by sending a reward value to store in the player inventory.
/////////////////////////////////////////////////////////////////////////////////////////
//Hierarchy Connections:
//Reward -HAS A-> Name
/////////////////////////////////////////////////////////////////////////////////////////
#include "reword.h"
using namespace std;
//Default constructor
//step 1: allcoate activatio table  to 5
//step 2: set tham to NULL
//Step 3: call read from reward.txt file 
reward::reward(): rewards(NULL), next(NULL), activation_table(NULL) 
{
    activation_table = new bool[5];
    rewards = new name[5];
    for(int i = 0; i < 5 ; ++i)
        activation_table[i] = false;
    read();
}
//step 1: allcoate activatio table to 5
//step 1: allcoate name table to 5
//step 2: for loop - set activation values to to_copy values
//step 3: set reward names
//Step 3: call copy function to copy recusivliy the to_copy next rewards list 
reward::reward(const reward & to_copy): rewards(NULL), next(NULL), activation_table(NULL) 
{
    activation_table = new bool[5];
    rewards = new name[5];
    for(int i = 0; i < 5 ; ++i)
    {
        activation_table[i] = to_copy.activation_table[i];
        rewards[i].set_name(to_copy.rewards[i]);
    }
    copy(to_copy.next, next);
}
//Step 1: check is the source is NULL
//step 2: allcate dest and pass address of source to it to copy
//step 3: call the function recursivliy 
void reward::copy(const reward * src, reward *& dest)
{
    if(!src)
        return;
    dest = new reward(*src);
    copy(src->next, dest->next);
}
//Step 1: allocate object of read 
//step 2: open the file
//step 3: check if load is not NULL
//step 4: if not end of file continue looping
//step 5: read to array temp
//step 6: call ganhe name function from reward 
//step 7: loop until end of file
//step 8 : close file 
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
//step 1: check if the passed in value is less than five 
//step 2: if actvation table is false change it to true
//step 3: if alrewady true - call recursivly to add in next
//step 4: Upon ending the recursive call after addtion it will display added item
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
//step 1: check if head is NULL
//step 2: if yes - aallocate head
//step 3: check if activatetion table has the reward already
//step 4: no - adds it and return 
//step 5: yes - call it self with next pointers
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
//step 1: check if passed in value if less than 5 or is equal nto -1 if yes return false
//step 2: check if use exisit in head
//step 3: if yes - turn it to false and return true
//step 4: if no - call recursive function  with next pointer
bool reward::use_reward(const int use)
{
    if(use > 5 || use == -1)
        return false;
    if(!activation_table[use])
        return use_reward(next, use);
    else
        return !(activation_table[use] = false);
}
//step 1: check if head is NULL
//step 2: yes - return
//step 3: check if use exixt 
//step 3: if yes - turn it to false and return true
//step 4: if no - call it recursively with next pointer
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
//step 1: make an int array and set it to zero
//step 2: call display recurvile to popilate the array 
//step 3: display the reward name and the number of how many does the user have
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
//step 1: check if head is NULL
//step 2: if no - for loop and populate the int array 
//step 3: call it self recursivly with next pointer
void reward::display(const reward * to_check, int * to_display)
{
    if(!to_check)
        return;
    for(int i = 0; i < 5; ++i)
        if(to_check->activation_table[i])
            ++to_display[i]; 
    display(to_check->next, to_display);
}
//step 1: check if head is NULL
//step 2: call it self recurvily
//step 3: delete head and set it to NULL
void reward::destroy(reward *& head)
{
    if(!head)
        return;
    destroy(head->next);
    delete head;
    head = NULL;
}
//Destrcutor
//Step 1: call destory on head
//step 2: delete reward arrays
//step 3: delete activation table array 
//step 4: set them to NULL
reward::~reward()
{
    destroy(next);
    delete [] rewards;
    delete [] activation_table; 
    activation_table = NULL;
    rewards = NULL;
}

