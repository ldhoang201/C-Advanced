#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\dllist.h"
#include"..\week3+\lib\dllist.c"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h" 

#define INFINITIVE_VALUE  10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph(){
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void add_Vertex(Graph g, int id, char* name){
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
         jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));            
}

char *get_Vertex(Graph g, int id){
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return NULL;
     else                
        return jval_s(node->val);
}     

double getEdgeValue(Graph g, int v1, int v2){
    JRB node, tree;
    node = jrb_find_int(g.edges, v1);
    if (node==NULL)
       return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INFINITIVE_VALUE;
    else
       return jval_d(node->val);       
}

void add_Edge(Graph g, int v1, int v2, double weight){
    JRB node, tree;
    if (getEdgeValue(g, v1, v2)==INFINITIVE_VALUE){
        node = jrb_find_int(g.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(g.edges, v1, new_jval_v(tree));
        } else {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

int comingVertex (Graph g, int v, int* output){
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, g.edges)
    {
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v))
       {
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;   
}

int outVertex(Graph g, int v, int* output){
    JRB tree, node;
    int total;
    node = jrb_find_int(g.edges, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
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

int hasEdge(Graph g, int v1, int v2) {
  JRB node;

  if ((node = jrb_find_int(g.edges, v1)) != NULL) {
    if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
      return 1;
    else return 0;
  } else return 0;
}

void deleteEdge(Graph g, int v1,int v2) {
    JRB node,node2;
    if(hasEdge(g,v1,v2)==0)
        return;
    else {
        JRB tree;
        node=jrb_find_int(g.edges,v1);
        tree=(JRB) jval_v(node->val);
        node2=jrb_find_int(tree,v2);
        jrb_delete_node(node2);
    }
}

void dropGraph(Graph g){ //free graph
    JRB node, tree;
    jrb_traverse(node, g.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(g.edges);
    jrb_free_tree(g.vertices);
}

int main(){
    int i, length, path[100], s, t , total;
    int output[30];
    double w;
    Graph g = createGraph();
    JRB node;
    add_Vertex(g, 0, "V0");
    add_Vertex(g, 1, "V1");
    add_Vertex(g, 2, "V2");
    add_Vertex(g, 3, "V3");
    add_Edge(g, 0, 1, 5);
    add_Edge(g, 1, 2, 9);
    add_Edge(g, 2, 0, 3);
    add_Edge(g, 1, 3, 1);
    add_Edge(g, 3, 2, 1);
    s = 3;
    t = 1;
    /*w = shortestPath(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE){
        printf("No path from %s to %s\n", get_Vertex(g, s), get_Vertex(g, t));
    } else {
        printf("Path from %s to %s (with total distance %.2f)\n", get_Vertex(g, s), get_Vertex(g, t), w);
        for (i=0; i<length; i++)
            printf("%5s", get_Vertex(g, path[i]));
    }*/
    jrb_traverse(node,g.vertices)
    {
        total = comingVertex(node,jval_i(node->key),output);
        for(int j = 0;j < total;j ++)
        {
            printf("%d ",output[j]);
        }
    }
    dropGraph(g);
    printf("\n"); 
}