#include<stdio.h>
#include<stdlib.h>
#include<D:\Codingz\C-advance\week3+\lib\jrb.c>
#include<D:\Codingz\C-advance\week3+\lib\jrb.h>
#include<D:\Codingz\C-advance\week3+\lib\jval.c>
#include<D:\Codingz\C-advance\week3+\lib\jval.h>
#include<D:\Codingz\C-advance\week3+\lib\dllist.c>
#include<D:\Codingz\C-advance\week3+\lib\dllist.h>
typedef JRB graph;
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
int main()
{
    int count,arr[20],getad;
    graph g;
    int total;
    g = graph_create();
    add_Egde(g, 0, 1);
    add_Egde(g, 1, 2);
    add_Egde(g, 1, 3);
    add_Egde(g, 2, 3);
    add_Egde(g, 2, 4);
    add_Egde(g, 4, 5);
    total = getAdjacentVertices(g,2,arr);
    printf("\n");
    return 0;
}