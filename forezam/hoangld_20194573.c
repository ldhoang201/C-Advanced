#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"..\week3+\lib\jrb.c"
#include"..\week3+\lib\jrb.h"
#include"..\week3+\lib\jval.c"
#include"..\week3+\lib\jval.h" // em dung windowns nen phai add ca file.c

typedef struct hoangld_20194573
{
  char domain[30];
  char ipadress[30];
}infor;


void do_print();
void do_add(char *dn, char *ip);
void do_remove(char *dn);
void do_lookup_ip(char *dn);
void do_lookup_dn(char *ip);

FILE * a;
infor info[30];
int num,count = 0;
JRB temp,bn;

int main(int argc, char **argv) {
  temp = make_jrb();
  a = fopen("dns.txt","r+");
  if(a == NULL)
  printf("Erorr!\n");
  else{
    fscanf(a,"%d",&num);
    while (!feof(a))
    {
      fscanf(a,"%s",info[count].domain);
      fscanf(a,"%s",info[count].ipadress);
      jrb_insert_str(temp,info[count].domain,new_jval_s(info[count].ipadress));
      count ++;
    }
  }
  if (argc <= 1) {
    printf("Usage: prog print \n       prog add [dn] [ip] \n       prog remove [dn]\n       prog ip [dn]\n       prog dn [ip]\n");
    return 0;
  }

  if (strcmp(argv[1], "print") == 0) {
    if (argc != 2) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_print();
    return 0;
  }
  if (strcmp(argv[1], "add") == 0) {
    if (argc != 4) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_add(argv[2], argv[3]);
    return 0;
  }
  if (strcmp(argv[1], "remove") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_remove(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "ip") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_ip(argv[2]);
    return 0;
  }
  if (strcmp(argv[1], "dn") == 0) {
    if (argc != 3) {
      printf("Invalid parameters\n");
      return 0;
    }
    do_lookup_dn(argv[2]);
    return 0;
  }
  printf("Invalid parameters\n");
  return 0;
}

void print_entry(char *dn, char *ip) {
  printf("%s => %s\n", dn, ip);  
}


void do_print() {
  jrb_traverse(bn,temp)
  {
    print_entry(bn->key.s,bn->val.s);
  }
}

void do_add(char *dn, char *ip) {
  FILE *ptr = fopen("dns.txt","a+");
  if(ptr == NULL)
  {
    printf("Erorr!\n");
  }
  else
  {
    fprintf(ptr,"\n");
    fprintf(ptr,"%s",dn);  // add xong quay lai case 1 de in a.
    fprintf(ptr,"\n");
    fprintf(ptr,"%s",ip);
  }
}

void do_remove(char *dn) {
}

void do_lookup_ip(char *dn) {
  JRB findingip;
  findingip = jrb_find_str(temp,dn);
  if(findingip != NULL)
  printf("%s => %s",dn,findingip->val.s);
  else printf("Not found!\n");
}

void do_lookup_dn(char *ip) {
  JRB findingdn;
  jrb_traverse(findingdn,temp)
  {
    if(strcmp(jval_s(findingdn->val),ip) == 0)
    printf("%s => %s",findingdn->key.s,ip);
    if((jrb_next(findingdn) == jrb_nil(temp)) && (strcmp(jval_s(findingdn->val),ip) != 0))
    printf("Not found!\n");
  }
}
