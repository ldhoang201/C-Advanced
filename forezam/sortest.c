#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "sort2wto3way.h"
int main()
{
    int a[20];
    srand(time(NULL));
    for(int j = 0;j < 10; j++)
    {
        a[j] = rand() % 50;
    }
    sort(a,0,9);
    for(int i = 0;i < 10; i++)
    {
        printf("%d\t",a[i]);
    }
}