#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h"
typedef struct w6hw
{
    char stations[30];
}sta;

typedef JRB graph;
graph graph_create()
{
    graph g;
    g = make_jrb();
    return g;
}
void add_Egde(graph g,int v1,int v2,char *s1,char *s2)
{
    graph tree;
    graph node = graph_create();
    if((node = jrb_find_int(g,v1)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v2,new_jval_s(s2));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_s(s2));
    }
    if((node = jrb_find_int(g,v2)) != NULL){
        tree = graph_create();
        tree = jval_v(node->val);
        jrb_insert_int(tree,v1,new_jval_s(s1));
    }
    else{
        tree = graph_create();
        jrb_insert_int(g,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_s(s1));
    }
}

void getAdjacentVertices(graph g, int v)
{
    int total = 0;
    graph node = graph_create();
    graph tree = graph_create();
    node = jrb_find_int(g,v);
    tree = jval_v(node->val);
    jrb_traverse(node ,tree )
    {
        printf("%s",node->val);
    }
}
void drop_graph(graph g)
{
    graph temp = graph_create();
    temp = jval_v(g->val);
    jrb_traverse(temp , g)
    {
        jrb_free_tree(jval_v(temp->val));
    }
}
int main()
{
    int cnt = 0;
    sta sta[20];
    graph g;
    FILE * ptr;
    ptr = fopen("stations.txt","r");
    g = graph_create();
    while (!feof(ptr))
    {
        fgets(sta[cnt].stations,"30",ptr);
        cnt++;
    }
    add_Egde(g,1,3,sta[1].stations,sta[3].stations);
    add_Egde(g,1,5,sta[1].stations,sta[5].stations);
    add_Egde(g,1,7,sta[1].stations,sta[7].stations);
    add_Egde(g,2,4,sta[2].stations,sta[4].stations);
    add_Egde(g,2,6,sta[2].stations,sta[6].stations);
    add_Egde(g,2,8,sta[2].stations,sta[8].stations);
    printf("Lines M1:S1,S3,S5,S7\n");
    getAdjacentVertices(g,1);
    printf("\n");
    printf("Lines M2:S2,S4,S6,S8\n");
    getAdjacentVertices(g,2);
    drop_graph(g);
    fclose(ptr);
    return 0;
}