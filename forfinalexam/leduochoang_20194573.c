#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h"
#include"..\week3+\lib\dllist.c"
#include"..\week3+\lib\dllist.h"
typedef JRB graph;
typedef struct dancu
{
    char CCCD[20];
    int SDT;
    char name[50];
    int id;
}dancu_data;

typedef struct tiepxuc
{
    char CCCD1[20],CCCD2[20];
    int time;
}tiepxuc_data;

graph graph_create()
{
    graph g;
    g = make_jrb();
    return g;
}
void add_Egde(graph g,int v1,int v2)
{
    graph tree;
    graph node = graph_create();
    if((node = jrb_find_int(g,v1)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v2,new_jval_i(1));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_i(1));
    }
    if((node = jrb_find_int(g,v2)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
}

int getAdjacentVertices(graph g, int v, int *output)
{
    int total = 0;
    graph node = graph_create();
    graph tree = graph_create();
    node = jrb_find_int(g,v);
    tree = jval_v(node->val);
    jrb_traverse(node ,tree )
    {
        output[total] = jval_i(node->key);
        total ++;
    }
    return total;
}

void BFS(graph graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, queue;
   
   queue = new_dllist();
   dll_append(queue, new_jval_i(start));

   while ( !dll_empty(queue) )
   {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(queue, new_jval_i(v));
          }
      }
   }                            
}

void DFS(graph graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, stack;
   
   stack = new_dllist();
   dll_append(stack, new_jval_i(start));

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(stack, new_jval_i(v));
          }
      }
   }                            
}

void printVertex(int v)
{
  printf("%4d",v);
}
void drop_graph(graph g)
{
    graph node = graph_create();
    node = g;
    jrb_traverse(node,g)
    {
        jrb_free_tree(jval_v(node->val));
    }
}

void menu()
{
    printf("-----------------Menu--------------------\n");
    printf("|1)Doc va in du lieu                    |\n");
    printf("|2)Dang ki 1 cong dan moi               |\n");
    printf("|3)Ghi nhan tiep xuc                    |\n");
    printf("|4)Tra cuu cong dan                     |\n");
    printf("|5)Tra cuu thong tin tiep xuc           |\n");
    printf("|6)Tra cuu mang luoi tiep xuc           |\n");
    printf("|_______________________________________|\n");
}

int main()
{
    FILE * ptr1 = fopen("dancu.txt","r");
    FILE * ptr2 = fopen("tiepxuc.txt","r");
    dancu_data data1[30];
    tiepxuc_data data2[30];
    char CCfind[30],TXfind[30];
    graph g = graph_create();
    int dancurecord,tiepxucrecord,count1 = 0,count2 = 0;
    int choice,dem = 0,tinh = 0,cnt = 0;
    fscanf(ptr1,"%d",&dancurecord);
    while (!feof(ptr1))
    {
        fscanf(ptr1,"%s",data1[count1].CCCD);
        fscanf(ptr1,"%d",&data1[count1].SDT);
        fscanf(ptr1,"%s",data1[count1].name);
        count1++;
    }
    fscanf(ptr2,"%d",&tiepxucrecord);
    for(int t = 0;t < count1; t ++)
    {
        if(data1[t].CCCD)
        data1[t].id = t +1 ;
    }
    printf("%d\n",data1[0].id);
    while (!feof(ptr2))
    {
        fscanf(ptr2,"%s %s %d",data2[count2].CCCD1,data2[count2].CCCD2,&data2[count2].time);
        count2++;
    }
    do{
        menu();
        printf("Your choice: ");scanf("%d%*c",&choice);
        switch (choice)
        {
            case 1:          
            printf("Thong tin Dan cu:\n");
            printf("So ban ghi:%d\n",dancurecord);
            for(int i = 0; i < count1 ; i++)
            {
                printf("%s %d %s\n",data1[i].CCCD,data1[i].SDT,data1[i].name);
            }
            printf("Thong tin tiep xuc:\n");
            printf("So ban ghi:%d\n",tiepxucrecord);
            for (int j = 0; j < count2; j++)
            {
                 printf("%s %s %d\n",data2[j].CCCD1,data2[j].CCCD2,data2[j].time);
            }
            printf("So Dinh:%d\n",tiepxucrecord + 1);
            printf("So Canh:%d\n",tiepxucrecord);
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            printf("Nhap CCCD muon tim:");gets(CCfind);
            for(int k = 0; k < count1 ; k++)
            {
                if(strcmp(data1[k].CCCD,CCfind) == 0)
                {
                    printf("Ten:%s\n",data1[k].name);
                    printf("SDT:%d\n",data1[k].SDT);
                    dem++;
                }
            }
            if(dem == 0)
            printf("Khong ton tai!\n");
            break;
            case 5:
            printf("Nhap CCCD muon tim:");gets(TXfind);
            if(strcmp(data2[0].CCCD1,TXfind) == 0)
            {
                printf("Tiep xuc voi:\n");
                printf("%s SDT:%d CCCD:%s Thoi gian tiep xuc:%d\n",data1[1].name,data1[1].SDT,data1[1].CCCD,data2[0].time);
                cnt ++;
            }
            else if(strcmp(data2[1].CCCD1,TXfind) == 0)
            {
                printf("Tiep xuc voi:\n");
                printf("%s SDT:%d CCCD:%s Thoi gian tiep xuc:%d\n",data1[2].name,data1[2].SDT,data1[2].CCCD,data2[1].time);
                cnt ++;
            }
            else printf("Khong co tiep xuc\n");
            break;
            case 6:break;
            default:
            printf("Rechoose from 1 to 6!\n");
            break;
        }
    }while(choice != 6);
    return 0;
}