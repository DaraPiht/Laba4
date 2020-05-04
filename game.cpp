#include <iostream>
#include "game.h"
#include <ctime>
using namespace std;


Game initGame(char userChar){
  srand(time(NULL));
    Game gra;

    gra.status=PLAY;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            gra.board[i][j]=' ';

    if((rand()%2))
       gra.isUserTurn=1;
    else
       gra.isUserTurn=0;

    gra.userChar=userChar;

    if(gra.userChar=='X')
    gra.botChar='O';
    else
      gra.botChar='X';

    return gra;
}
void updateDisplay(const Game game)
{
 system("cls");
    cout<<"\t0\t1\t2\n";
 for(int i=0;i<3;i++)
{
    cout << i << '\t';
     for(int j=0;j<3;j++)
         cout<< game.board[i][j] << '\t';
         cout << '\n';
}

}

void botTurn(Game* game){
    bool isEmpty = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game->board[i][j] != ' ') isEmpty = false;
        }
    }
    if (isEmpty) {
     game->board[1][1]=game->botChar;
     return;
    }

    int kolvoX=0;
    for (int i = 0; i < 3; i++) {
         kolvoX=0;
        for (int j = 0; j < 3; j++) {
           if(game->board[i][j]==game->userChar){
               kolvoX++;
               if(kolvoX==2)
                   for(int j2=0;j2<3;j2++){
                       if(game->board[i][j2]==' '){
                           game->board[i][j2]=game->botChar;
                           return;
                       }
                   }
               }
           }
       }

    int kolvoY=0;
 for (int j = 0; j < 3; j++) {
         kolvoY=0;
    for (int i = 0; i < 3; i++) {
           if(game->board[i][j]==game->userChar){
               kolvoY++;
               if(kolvoY==2)
                   for(int i2=0;i2<3;i2++){
                       if(game->board[i2][j]==' '){
                           game->board[i2][j]=game->botChar;
                           return;
                       }
                   }
               }
           }
       }

       int main_diag=0;
     for(int i=0;i<3;i++){
         if(game->board[i][i]==game->userChar){
             main_diag++;
             if(main_diag==2){
                 for(int i2=0;i2<3;i2++){
                     if(game->board[i2][i2]==' '){
                         game->board[i2][i2]=game->botChar;
                         return;
                     }
                 }
             }
         }
     }

 int dop_diag=0;
for(int i=0;i<3;i++){
   if(game->board[i][2-i]==game->userChar){
       dop_diag++;
       if(dop_diag==2){
           for(int i2=0;i2<3;i2++){
               if(game->board[i2][2-i2]==' '){
                   game->board[i2][2-i2]=game->botChar;
                   return;
               }
           }
       }
   }
}

    //Random
    int rRow;
    int rCol;
    do{
        rRow = rand() % 3;
        rCol = rand() % 3;
    }
    while (game->board[rRow][rCol] != ' ');
    game->board[rRow][rCol] = game->botChar;
}

void userTurn(Game* game){
    while(true){
        cout<<"X Y: ";
        int x,y;
        cin>>x>>y;

        if((x<0 || x>2)||(y<0 || y>2)|| (game->board[x][y]!=' ')){
            cout<<"Error.\n";
            continue;
        }

        game->board[x][y]=game->userChar;
        break;
    }
}
bool updateGame(Game* game){
    game->isUserTurn=!game->isUserTurn;
        int user_rows[3] = {0,0,0};
        int user_cols[3] = {0,0,0};
        int user_diags[2] = {0,0}; // 0 - главная, 1 - побочная

        int bot_rows[3] = {0,0,0};
        int bot_cols[3] = {0,0,0};
        int bot_diags[2] = {0,0}; // 0 - главная, 1 - побочная


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game->board[i][j] == game->userChar) {
                    user_rows[i]++;
                    user_cols[j]++;
                    if (i == j) user_diags[0]++;
                    if (i == 2 - j) user_diags[1]++;

                    if (user_rows[i] == 3 || user_cols[j] == 3 || user_diags[0] == 3 || user_diags[1] == 3) {
                       game->status = USER_WIN;
                        return true;
                    }
                }
                else if (game->board[i][j] == game->botChar) {
                    bot_rows[i]++;
                    bot_cols[j]++;
                    if (i == j) bot_diags[0]++;
                    if (i == 2 - j) bot_diags[1]++;
                        game->status = BOT_WIN;
                    if (bot_rows[i] == 3 || bot_cols[j] == 3 || bot_diags[0] == 3 || bot_diags[1] == 3) {

                        return true;
                    }
                }
            }
            }
            // Проверка на ничью
                bool isDraw = true;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (game->board[i][j] == ' ') isDraw = false;
                    }
                }
                if (isDraw) {
                    game->status = NOT_WIN;
                    return true;
                }
    return false;
}
