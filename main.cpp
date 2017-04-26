#include "cs_maze_game.h"
using namespace std;

int main()
{
    srand(time(0));
  /*  cs_maze a(5);
    player b("b",2);
    a.start(b);
    b.display_location();
    a.display_map();
    a.move_player(b, 0);
    cout<<"\n-------\n";
    a.display_map();
    b.display_location();*/
    cs_maze_game l;
    l.start();
/*    srand(time(0));
    cs_maze r;
    player m;
   // r.display_chocies(m);
    r.display_map();
    reward t;
    t.activate_reward(0);
    t.activate_reward(0);
    t.activate_reward(0);
    t.activate_reward(0);
    t.activate_reward(0);
    t.activate_reward(0);
    t.activate_reward(3);
    cout<<t.use_reward(0);
    cout<<t.use_reward(0);
    t.display();
    vertex_CP q("a",2);
    vertex_CP w("b",2);
    vertex_CP e("c",2);
    q.add_path(w);
    q.add_path(e);
    q.display_connections();
    player * a = new player("A",0);
    player b("B",0);
    a->display();
    cout<<"----i\n";
    b.create_table(2);
    b.add_player(b);
    b.add_player(b);
    b.add_player(*a);
    b.display_players();

    cout<<"----i\n";
    cout<<b.isMember(*a);
    b.remove_player(*a);
    cout<<b.isMember(*a);
    delete a;
    a = NULL;
    b.display_players();
    cout<<"----i\n";
    q.add_player(b);

    cout<<"q before: \n";
    q.display_players();
    q.move_player(b,w);
    cout<<"q after: \n";
    q.display_players();
    cout<<"w now:  \n";
    w.display_players();
    cout<<q.isBlock();
    cout<<"\n reward: ";
    cout<<w.trigger_reward()<<endl;
   // location l(a);
//    l location("zack");
  //  p location(l);
   // p.display();*/
    return 0;
}
