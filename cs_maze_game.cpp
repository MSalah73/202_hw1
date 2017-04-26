#include "cs_maze_game.h"
using namespace std;

cs_maze_game::cs_maze_game():players_table(NULL), table_size(0)
{
}
cs_maze_game::cs_maze_game(const cs_maze_game & to_copy):players_table(NULL), table_size(0)
{
    maze = new cs_maze(*to_copy.maze);
    table_size = to_copy.table_size;
    if(table_size)
    {
        players_table = new player[table_size];
        for(int i = 0; i < table_size; ++i)
            players_table[i].copy_members(to_copy.players_table[i]);
    }
}
void cs_maze_game::start()
{
    bool quit = false;
    cout<<"Welcone to the randomized maze game. The rules is to "
        <<"reach the winnning check point before the other team does\n"
        <<"\33[0;31mDISCLAIMER: You can uncomment out maze->display_map() - file cs_maze_game line 29, if you are having a hard time findng the winning checkpoint \33[0m\n\n";
    set_tables();
    int Turn = (random() % table_size);
    set_teams();
    for(int i = 0; i < table_size; ++i)
        maze->start(players_table[i]);
    //maze->display_map();
    do
    {
        Turn %= table_size;
        cout<<"\n\33[0;31m------P"<<(Turn+1)<<" Turn------\33[0m\n";
        if(players_table[Turn].isParalyzed())
        {
            cout<<"\33[0;31munfortunately he/she is paralyzed! - Player will be recovered next turn\33[0m\n";
            players_table[Turn].change_effect();
        }
        else
        {
            players_table[Turn].display();
            quit = menu(Turn);
        }
        ++Turn;
    }while(!quit ^ maze->check_winner());
}
void cs_maze_game::set_tables()
{
    char temp[100] = {0};
    do
    {
        cout<<"Please enter an even number of players - minimum 4 - maximum 8\n";
        cin>>table_size;
        cin.ignore(100,'\n');
        if(table_size % 2)
            table_size = 0;
    }while(!(table_size > 3 && table_size < 9));
    maze = new cs_maze(table_size);
    players_table = new player[table_size];
    for(int i = 0; i < table_size; ++i)
    {
        cout<<"Please enter a name for P"<<i+1<<endl;
        cin.get(temp, 100, '\n');
        cin.ignore(100, '\n');
        players_table[i].create_table(table_size/2);
        players_table[i].change_name(temp);
    }
}
void cs_maze_game::set_teams()
{
    int j, tsize;
    for(int i = 0; i < table_size; ++i)
    {
        if(i < table_size/2)
        {
            j = 0;
            tsize = table_size/2;
        }
        else
        {
            j = table_size/2;
            tsize = table_size;
        }
        for(;j < tsize ;++j)
            if(!(&players_table[i] == &players_table[j]))
                players_table[i].add_player(players_table[j]);
    }
}
bool cs_maze_game::menu(int to_play)
{
    int choice = 0; 
    do
    {
        cout<<"\nPlease pick a number associated with one of options below"
            <<"\nWhat would you like to do ?\n"
            <<"1 - Move to a location\n"
            <<"2 - Use a reward\n"
            <<"3 - Display options\n"
            <<"4 - Quit\n";
        cin>>choice;
        cin.ignore(100, '\n');
        if(choice == 1)
            choice = turn(players_table[to_play]);
        else if(choice == 2)
            choice = reward_menu(to_play);
        else if(choice == 3)
            choice = display_options(to_play);
    }while(!(choice > 0 && choice < 5));
    if(choice == 4)
        return true;
    return false;
}
int cs_maze_game::display_options(int Turn)
{
    int choice = 0;
    do{
        cout<<"\nPlease pick a number associated with one of options below"
            <<"\nWhat would you like to display ? \n"
            <<"1 - Display player's infomation\n"
            <<"2 - Display current location\n"
            <<"3 - Display friends\n"
            <<"4 - Display friend's locations\n"
            <<"5 - Display current rewards\n"
            <<"6 - Display paths\n"
            <<"7 - Previous menu\n"
            <<"8 - Quit\n";
        cin>>choice;
        cin.ignore(100,'\n');
    }while(!(choice > 0 && choice < 9));

    if(choice == 1)
        players_table[Turn].display_info();
    else if(choice == 2)
        players_table[Turn].display_location();
    else if(choice == 3)
        players_table[Turn].display_players();
    else if(choice == 4)
        players_table[Turn].display_players_locations();
    else if(choice == 5)
    {
        cout<<"\33[0;31m-----Rewards inventory-----\33[0m\n";
        players_table[Turn].display_rewards();
    }
    else if(choice == 6)
    {
        cout<<"\n\33[0;31m-----Possible paths to take-----\33[0m\n";
        players_table[Turn].display_paths();
    }
    else if(choice == 8)
        return 4;
    return 0;
}
bool cs_maze_game::turn(player & to_play)
{
    int choice = 0;
    do{
        to_play.display_location();
        cout<<"\nPlease pick a number associated with one of options below"
            <<"\nWhere would like to go ?\n"
            <<"0 - Previous menu\n";
        to_play.display_paths();
        cin>>choice;
        cin.ignore(100,'\n');
    }while(!(choice) ^ !to_play.isValid_path((choice-1)));
    if(!choice)
        return false;
    --choice;
    maze->move_player(to_play, choice);
    return 1;
}
bool cs_maze_game::reward_menu(int Turn)
{
    int choice = 0;
    do{
        cout<<"Please pick a number associated with one of options below"
            <<"\nWhere would like to use ? NOTE: (#) Is amount you current have\n"
            <<"0 - Previous menu\n";
        players_table[Turn].display_rewards();
        cin>>choice;
        cin.ignore(100,'\n');
    }while(!(choice) ^ !players_table[Turn].use_reward((choice-1)));
    if(!choice)
        return false;
    activate_reward((choice-1), Turn);
    return false;
}
void cs_maze_game::activate_reward(const int use, int Turn)
{
    if(!use)
    {
        int to_para = -1;
        if(Turn < table_size/2)
            to_para = (random() % table_size/2) + 2;
        else 
            to_para = (random() % table_size/2);
        players_table[to_para].change_effect();
        cout<<"\33[0;31mP"<<(Turn+1)<<" have casted a paralyze spell!\n"
            <<"It effected P"<<(to_para+1)<<"!\33[0m\n";
    }
    else if(use == 1)
    {
        int to_steal = -1, list_plys = 0;
        bool stolen = false;
        if(Turn < table_size/2)
        {
            to_steal = table_size/2;
            list_plys = table_size;
        }
        else 
        {
            to_steal = table_size/2 - 2;
            list_plys = table_size/2;
        }
        for(int i = to_steal; i < list_plys && !stolen; ++i)
            for(int j = 0; j < 5 && !stolen; ++j)
                if(players_table[i].use_reward(j))
                {
                    cout<<"\33[0;31mRewards below has been stolen\33[0m\n";
                    players_table[Turn].add_reward(j);
                    stolen = true;
                }
        if(!stolen)
            cout<<"\33[0;31mFailed to steal rewards\33[0m\n";
    }
    else if(use == 2)
    {
        bool used = turn(players_table[Turn]);
        if(!used)
        {
            cout<<"\33[0;31mBelow is a cancled reward - add back to inventory\33[0m\n";
            players_table[Turn].add_reward(use);
        }
    }
    else if(use == 3)
        maze->move_to_friend(players_table[Turn]);
    else
        maze->move_to_enemy(players_table[Turn]);
}
cs_maze_game::~cs_maze_game()
{
    delete [] players_table;
    delete maze;
}
