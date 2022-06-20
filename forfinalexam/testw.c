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
void add_Egde(graph g,int v1,int v2,double weight)
{
    graph tree;
    graph node = graph_create();
    if((node = jrb_find_int(g,v1)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v2,new_jval_d(weight));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_d(weight));
    }
    if((node = jrb_find_int(g,v2)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v1,new_jval_d(weight));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_d(weight));
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

double shortestPath(Graph g, int s, int t, int* path, int*length){
    double distance[1000], min, w, total;
    int previous[1000], tmp[1000];
    int n, output[100], i, u, v, start;
    Dllist queue, node;

    for (i=0; i<1000; i++)
        distance[i] = INFINITIVE_VALUE;
    distance[s] = 0;
    previous[s] = s;
       
    queue = new_dllist();
    if(!jrb_find_int(g.vertices,s)) return INFINITIVE_VALUE;
    dll_append(queue, new_jval_i(s));

    while ( !dll_empty(queue) ){
        dll_traverse(node, queue)
            u = jval_i(node->val);                            
     
        if (u == t) break; // stop at t
        n = outVertex(g, u, output);
        for (i=0; i<n; i++){
	    //xet cac lan can v cua u
            v = output[i];
            w = getEdgeValue(g, u, v);
            if ( distance[v] > distance[u] + w ) {  //neu s.v > s.u thi cap nhat lai    
                distance[v] = distance[u] + w;
                previous[v] = u;
            }     
            dll_append(queue, new_jval_i(v));  //cho v vao trong queue
        }
    }
   
    total = distance[t]; //tim duoc khoang cach
   
    if (total != INFINITIVE_VALUE) {
        tmp[0] = t;
        n = 1;              
        while (t != s) {
            t = previous[t];
            tmp[n++] = t;
        }
        for (i=n-1; i>=0; i--)
	        path[n-i-1] = tmp[i]; //mang path la dao lon cua mang t
        *length = n;                
    }
    return total;   
}

int main()
{
    graph g = graph_create();
    int length,path[100],s,t;
    add_Egde(g,1,2,1);
    add_Egde(g,1,3,1);
    add_Egde(g,2,3,1);
    add_Egde(g,2,4,2);
    add_Egde(g,2,5,3);
    add_Egde(g,3,6,4);
    s = 2;
    t = 0;
    w = shortestPath(g, s, t, path, &length);
    printf("Path from %s to %s (with total distance %.2f)\n", getVertex(g, s), getVertex(g, t), w);
    for (i=0; i<length; i++)
    printf("%5s", getVertex(g, path[i]));
    return 0;
}