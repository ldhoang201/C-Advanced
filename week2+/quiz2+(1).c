#include<stdio.h>
#include<stdlib.h>
int int_compare(void * x, void * y) 
{
    int m, n;
    m = *((int*)x);
    n = *((int*)y);
    if ( m == n ) 
    return 0;
    return m > n? 1: -1;
}
void exch (void * buf, int size, int a, int b);  
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void sort(void *a, int size, int l, int r,int (*compare)(void*, void*))
{
    if (r <= l) return;
    int i = l-1, j = r;
    int p = l-1, q = r;
    while(1){
    while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
    while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )if (j == l) break;
    if (i >= j) break;exch(size, a[i], a[j]);
    if (compare((char*)a+i*size, (char*)a+r*size)==0)
    exch(size,a[++p], a[i]);
    if (compare((char*)a+j*size, (char*)a+r*size)==0)
    exch(size, a[--q], a[j]);
    }
    exch(size, a[i],a[r]);
    j = i -1;i = i + 1;
    for (int k = l ; k <= p; k++) 
    exch(size, a[k], a[j--]);
    for (int k = r-1; k >= q; k--) 
    exch(size, a[k], a[i++]);
    sort(a, size, l, j, compare);sort(a, size, i, r, compare);
}
int main()
{
    int a[]={1,5,2,8,0,9,3};
    sort(a,sizeof(int),0,6,int_compare);
    for(int i=0;i<6;i++)
    {
        printf("%d\t",a[i]);
    }
    return 0;
}