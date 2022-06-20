#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100000
int compare(void* a,void* b)
{
    int m,n;
    m = *(int*)a;
    n = *(int*)b;
    if (m == n) return 0;
    return m > n ? 1 : -1;
}
void swap(void *a,void* b,int size)
{
    void * buff=malloc(size);
    memcpy(buff,a,size);
    memcpy(a,b,size);
    memcpy(b,buff,size);
    free(buff);
}
void exch(void* a, int size, int i,int r)
{
    void *buffer=malloc(size);
    memcpy(buffer, a+size*i, size);
    memcpy(a+size*i, a+size*r, size);
    memcpy(a+size*r, buffer, size);
    free(buffer);
}
void sort2way(void* v, int size, int left, int right,int (*comp)(void*, void*))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;
    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {
        vt = (char*)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char*)(v + (last * size));
    swap(vl, v3, size);
    sort2way(v, size, left, last - 1, comp);
    sort2way(v, size, last + 1, right, comp);
}
void sort3way(void * a, int size, int l, int r,int(*compare)(void*,void *)) {
    if (r <= l) return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1) {
      while (compare((char*)a+(++i)*size,(char*) a +r*size) < 0);
      while (compare((char*)a+r*size,(char*) a +(--j)*size) < 0)
        if (j == l) break;
      if (i >= j) break;
      exch(a, size, i, j);
      if (compare((char*)a+i*size,(char*)a+r*size)==0)
        exch(a,size,++p,i);
      if (compare((char*)a+j*size,(char*)a+r*size)==0)
        exch(a,size,--q,j);
    }
    exch(a, size, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++) exch(a, size, k, j--);
    for (int k = r - 1; k >= q; k--) exch(a, size, k, i++);
    sort3way(a, size, l, j, compare);
    sort3way(a, size, i, r, compare);
}
int main()
{
    int a[MAX];
    clock_t begin,end;
    double t1,t2,t3;
    for(int i=0;i<MAX;i++)
    {
        a[i]=rand() %50;
    }
    begin = clock();
    sort2way(a,sizeof(int), 0, MAX-1,compare);
    t1 = (double)(clock() - begin); 
    printf("sort2way: %.2fs\n", t1);
    begin = clock();
    sort3way(a,sizeof(int), 0, MAX-1,compare);
    t2 = (double)(clock() - begin);
    printf("sort3way: %.2fs\n", t2);
    begin=clock();
    qsort(a,MAX,sizeof(int),compare);
    t3 = (double)(clock() - begin);
    printf("qsort: %.2fs\n", t3);
    return 0;
}