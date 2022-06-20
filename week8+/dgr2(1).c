#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\dllist.h"
#include"..\week3+\lib\dllist.c"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h"
typedef struct {
  JRB vertices;
  JRB edges;
} Graph;

Graph createGraph() {
  Graph g;
  g.vertices = make_jrb();
  g.edges = make_jrb();
  return g;
}

void add_Vertex(Graph g, int id, char* name) {
  JRB node = jrb_find_int(g.vertices, id);
  
  if (node == NULL)
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

void addEdge(Graph g, int v1, int v2) {
  JRB node, l;
  
  node = jrb_find_int(g.edges, v1);
  if (node != NULL) {
    l = (JRB)jval_v(node->val);
    jrb_insert_int(l, v2, new_jval_i(1));
  } else {
    l = make_jrb();
    jrb_insert_int(l, v2, new_jval_i(1));
    jrb_insert_int(g.edges, v1, new_jval_v(l));
  }

}

char *getVertexName(Graph g, int id) {
  JRB node = jrb_find_int(g.vertices, id);
  
  if (node != NULL)
    return jval_s(node->val);
  else return NULL;
}

int getVertexId(Graph g, char *name) {
  JRB i;

  jrb_traverse(i, g.vertices) {
    if (strcmp(name, jval_s(i->val)) == 0)
      return jval_i(i->key);
  }
  return -1;
}


int hasEdge(Graph g, int v1, int v2) {
  JRB node;

  if ((node = jrb_find_int(g.edges, v1)) != NULL) {
    if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
      return 1;
    else return 0;
  } else return 0;
}

void deleteEdge(Graph graph, int v1,int v2) {
    JRB node,node2;
    if(hasEdge(graph,v1,v2)==0)
        return;
    else {
        JRB tree;
        node=jrb_find_int(graph.edges,v1);
        tree=(JRB) jval_v(node->val);
        node2=jrb_find_int(tree,v2);
        jrb_delete_node(node2);
    }
}
Dllist outgoingVertices(Graph g, int v) {
  JRB node, l, i;
  Dllist output = new_dllist();
 
  if ((node = jrb_find_int(g.edges, v)) == NULL)
    return output;

  l = (JRB)jval_v(node->val);
  jrb_traverse(i, l) {
    dll_append(output, i->key);
  }
  return output;
}

Dllist incomingVertices(Graph g, int v) {
  JRB node, l, i;
  Dllist output = new_dllist();

  jrb_traverse(node, g.edges) {
    l = (JRB)jval_v(node->val);
    if (jrb_find_int(l, v) != NULL)
      dll_append(output, node->key);
  }
  return output;
}

void BFS(Graph g, int source, int dest, void (*f)(int key)) {
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;
  
  dll_append(q, new_jval_i(source));
  while (!dll_empty(q)) {
    n = dll_first(q);
    u = jval_i(dll_val(n));
    dll_delete_node(n);
    if (jrb_find_int(visited, u) == NULL) {
      f(u);
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = outgoingVertices(g, u);

      dll_traverse(n, adjs) {
	if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
	  dll_append(q, dll_val(n));
	if (jval_i(dll_val(n)) == dest) {
	  free_dllist(adjs);
	  jrb_free_tree(visited);
	  free_dllist(q);
	  return;
	}
      }
      free_dllist(adjs);
    }
  }
  jrb_free_tree(visited);
  free_dllist(q);
}

void DFS(Graph g, int source, int dest, void (*f)(int key)) {
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;
  
  dll_append(q, new_jval_i(source));
  while (!dll_empty(q)) {
    n = dll_last(q);
    u = jval_i(dll_val(n));
    dll_delete_node(n);
    if (jrb_find_int(visited, u) == NULL) {
      f(u);
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = outgoingVertices(g, u);

      dll_traverse(n, adjs) {
	if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
	  dll_append(q, dll_val(n));
	if (jval_i(dll_val(n)) == dest) {
	  free_dllist(adjs);
	  jrb_free_tree(visited);
	  free_dllist(q);
	  return;
	}
      }
      free_dllist(adjs);
    }
  }
  jrb_free_tree(visited);
  free_dllist(q);
}

int outdegree(Graph graph,int v,int* output) {
    JRB node,tree;
    int total;
    node=jrb_find_int(graph.edges,v);
    if(node==NULL)
        return 0;
    else {
        tree=(JRB) jval_v(node->val);
        total=0;
        jrb_traverse(node,tree)
	        output[total++]=jval_i(node->key);
        return total;
    }
}

int indegree(Graph graph,int v,int*output) {
    JRB node,tree;
    node=NULL;
    int key;
    int total;
    total=0;
    jrb_traverse(node,graph.vertices) {
        key = jval_i(node->key);
        if(hasEdge(graph,key,v)==1&&key!=v)
	        output[total++]=key;
    }
    return total;
}

int onCycle(Graph g, int v) {
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;
  
  dll_append(q, new_jval_i(v));
  while (!dll_empty(q)) {
    n = dll_last(q);
    u = jval_i(dll_val(n));
    dll_delete_node(n);
    if (jrb_find_int(visited, u) == NULL) {
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = outgoingVertices(g, u);

      dll_traverse(n, adjs) {
	if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
	  dll_append(q, dll_val(n));
	if (hasEdge(g, jval_i(dll_val(n)), v)) {
	  free_dllist(adjs);
	  jrb_free_tree(visited);
	  free_dllist(q);
	  return 1;
	}
      }
      free_dllist(adjs);
    }
  }
  jrb_free_tree(visited);
  free_dllist(q);
  return 0;
}

int isDAG(Graph g) {
  JRB node;
  jrb_traverse(node, g.vertices) {
    if (onCycle(g, jval_i(node->key)))
      return 0;
  }
  return 1;
}

void dropGraph(Graph g) {
  JRB i;

  jrb_traverse(i, g.vertices) {
    free(jval_v(i->val));
  }
  jrb_free_tree(g.vertices);

  jrb_traverse(i, g.edges)
    jrb_free_tree((JRB)jval_v(i->val));
  jrb_free_tree(g.edges);
}

void printVertex(int v) { 
    printf("%4d", v); 
}

typedef struct dgr2
{
    char name[30];
    int id;
}info;

int main()
{
    info infor[20];
    int a[20],count = 0;
    int in,out;
    Graph g;
    g = createGraph();
    add_Vertex(g,0,"F");
    add_Vertex(g,1,"A");
    add_Vertex(g,2,"B");
    add_Vertex(g,3,"C");
    add_Vertex(g,4,"D");
    add_Vertex(g,5,"E");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 0, 4);
    addEdge(g, 4, 1);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 0, -1, printVertex);
    printf("\nDFS: start from node 1 to all : ");
    DFS(g, 0, -1, printVertex);
    dropGraph(g);
    return 0;
}