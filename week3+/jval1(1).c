#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<D:\Codingz\File saving\.vscode\week3+\lib\jval.h>
#include<D:\Codingz\File saving\.vscode\week3+\lib\jval.c>
#include<D:\Codingz\File saving\.vscode\week3+\lib\dllist.h>
#include<D:\Codingz\File saving\.vscode\week3+\lib\dllist.c>
#include<D:\Codingz\File saving\.vscode\week3+\lib\jrb.h>
#include<D:\Codingz\File saving\.vscode\week3+\lib\jrb.c>
#include<D:\Codingz\File saving\.vscode\week3+\lib\fields.h>
#include<D:\Codingz\File saving\.vscode\week3+\lib\fields.c>
#define MAX 20
int compare_jval_int(Jval *a,Jval *b)
{
    if(jval_i(*a) == jval_i(*b))
    return 0;
    else if(jval_i(*a) > jval_i(*b))
    return 1;
    else return -1;
}
void exch(Jval a[],int i,int j)
{
    Jval temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}
void quicksort(Jval a[], int l,int r,int (*compare_int)(Jval*,Jval*))
{
    if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (compare_int(a + (++i),a + r) == -1);
		while (compare_int(a + r,a + (--j)) == -1); if (j == l) break;
		if (i >= j) break;
		exch(a,i,j);
		if (compare_int(a + i,a + r) == 0) exch(a,++p,i);
		if (compare_int(a + j,a + r) == 0) exch(a,--q,j);
	}
	exch(a,i,r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a,k,j--);
	for (int k = r-1; k >= q; k--) exch(a,k,i++);
	quicksort(a, l, j,compare_int);
	quicksort(a, i, r,compare_int);
}
int binary_search(Jval arr[],int left,int right,Jval *key,int (*compare_int)(Jval*,Jval*))
{
  if(left <= right)
  {
  int mid = (left + right) / 2;
  if(compare_int(arr + mid,key) == 0)
  return mid;
  else if(compare_int(arr + mid,key) == 1)
  return binary_search(arr,left,mid-1,key,compare_int);
  else if(compare_int(arr + mid,key) == -1)
  return binary_search(arr,mid+1,right,key,compare_int);
  return -1;
  }
}
int main()
{
    Jval a[MAX];
    srand(time(NULL));
    int x,z;
    Jval b;
    for (int i = 0; i < MAX; i++)
    {
        a[i]=new_jval_i(rand()%100);
    }
    quicksort(a,0,MAX-1,compare_jval_int);
    for (int j = 0; j < MAX; j++)
    {
        printf("%d ",jval_i(a[j]));
    }
    printf("\n");
    printf("Ban muon tim bao nhieu so :");scanf("%d",&z);
    for(int k = 0;k < z; k++)
    {
        printf("Nhap so can tim :");scanf("%d",&x);
        b=new_jval_i(x);
        printf("%d\n",binary_search(a,0,MAX-1,&b,compare_jval_int));
    }
    return 0;
}