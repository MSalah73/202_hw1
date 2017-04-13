#include "name_location.h"
using namespace std;

int main()
{
    player * a = new player("A");
    player b("B");
    a->display();
    b.create_array(2);
    b.add_player(b);
    b.add_player(b);
    b.add_player(*a);
    b.display_team();

    cout<<b.isTeammate(*a);
    b.remove_teammate(*a);
    cout<<b.isTeammate(*a);
    delete a;
    a = NULL;
    b.display_team();
   // location l(a);
//    l location("zack");
  //  p location(l);
   // p.display();
    return 0;
}
