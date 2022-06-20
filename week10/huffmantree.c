#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\dllist.h"
#include"..\week3+\lib\dllist.c"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h"

int dem(char *p,int i)
{
   int dem=0;
   for (int j=i;j<strlen(p);j++)
   {
       if(p[i]==p[j]) dem++;
   }
   return dem;
}

typedef struct {
    int size;
    char bits[2];
} Coding;

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

void addVertex(Graph g, int id, char* name) {
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

typedef struct huffmantree
{
    Graph graph;
    JRB root;
} HuffmanTree;

HuffmanTree make_HuffmanTree(char * buffer,int size1)
{
    Dllist queue;
    queue = new_dllist();
    buffer = (char*)malloc(size1);
    for(int i = 0;i < size1;i ++)
    {
        int min = dem(buffer,i);
        for (int j = 0; j < size1; j++)
        {
            if(dem(buffer,j) < min)
            dll_append(queue,new_jval_d(dem(buffer,j)));
        }
    }
}
int main()
{
    Coding huffmanTable[256];
    Graph g = createGraph();
    return 0;
}