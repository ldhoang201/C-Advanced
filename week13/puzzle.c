#include<stdio.h>
#include<stdlib.h>
typedef struct puzzle
{
    int config[3][3];
    int x,y;
}puzzle;

void create_puzzle(puzzle *puzz)
{
    int n = 1;
    for(int i = 0;i < 3;i ++)
        for(int y = 0;y < 3;y ++)
        {
            puzz->config[i][y] = n;
            n ++;
        }
        puzz->config[2][2] = 0;
        puzz->x = puzz->y = 3;
}
int main()
{
    puzzle puzz;
    int count = 0;
    create_puzzle(&puzz);
    for(int i = 0;i < 3;i ++)
        for(int y = 0;y < 3;y ++)
        {
           printf("%d\t",puzz.config[i][y]);
           count ++;
           if(count % 3 == 0)
           printf("\n");
        }
    return 0;
}