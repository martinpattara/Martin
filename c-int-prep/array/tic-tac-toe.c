#include <stdio.h>
#include <stdlib.h>

int moves = 0;

static int game_over(int g[3][3])
{
    if (moves == 9) {
        printf("Moves are over\n");
        return 1;
    }
    return 0;

}

int main()
{
   int x, y, i, j;
   int g[3][3];
   printf("\e[2J\e[H");

   printf("Welcome to tic tac toe game\n");
   while (1) {
       printf("Player A please make a move\n");
       printf("Enter your x and y cordinate\n");
       scanf("%d", &x);
       scanf("%d", &y);
       g[x][y] = 'x';
       if (game_over(g)) {
          printf("Game over\n");
       }
       printf("\e[2J\e[H");
       printf("Player B please make a move\n");
       printf("Enter your x and y cordinate\n");
       scanf("%d", &x);
       scanf("%d", &y);
       g[x][y] = 'o';
       if (game_over(g)) {
          printf("Game over\n");
       }
       printf("\e[2J\e[H");
   }
   return 0;
}
