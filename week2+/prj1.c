#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 50
int int_compare(void* a,void* b)
{
    int m,n;
    m = *(int*)a;
    n = *(int*)b;
    if (m == n) return 0;
    return m > n ? 1 : -1;
}
int search( void* buf,int size,int l, int r,void * item,int (*compare)(void*, void*)) {
    if (r < l) return -1;
    int i = (l + r)/2;
    int res = compare( item, (char*)buf+(size*i) );
    if (res==0)
    return i;
    else if (res < 0)
    return search(buf, size, l, i-1, item, compare);
    else
    return search(buf, size, i+1, r, item, compare);
}
int main()
{
    int a[MAX];
    int b,index;
    srand(time(NULL));
    for(int i = 0;i < 10;i ++)
    {
        a[i]=rand() % 20;
    }
    for(int j = 0;j < 10;j ++)
    {
        printf("%2d\t",a[j]);
    }
    printf("\n");
    printf("Input the num you wanna find:");scanf("%d",&b);
    index=search(a,sizeof(int),0,9,&b,int_compare);
    printf("The index of %d:%d\n",b,index);
    return 0;
}