#include <iostream>
#include "game.h"
using namespace std;

int main()
{
    Game gra=initGame('X');
    updateDisplay(gra);

while(true){
    updateDisplay(gra);
    if (gra.isUserTurn)
        userTurn(&gra);
    else
        botTurn(&gra);
    updateDisplay(gra);

    if (updateGame(&gra)==true)
       break;
}

    switch(gra.status)
    {
    case BOT_WIN:
        cout<<"BOT WIN";
        break;
    case USER_WIN:
        cout<<"USER WIN";
        break;
    case NOT_WIN:
        cout<<"DRAW";
        break;
    default:
        cout<<"ERROR";
        break;
    }
 return 0;
}
