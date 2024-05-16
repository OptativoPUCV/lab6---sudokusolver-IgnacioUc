#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int i,j;
   int *fila = (int*) calloc(9,sizeof(int));
   int *columna = (int*) calloc(9,sizeof(int));
   int *cuadro = (int*) calloc(9,sizeof(int));
   for(i=0;i<9;i++){
      for(j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
            if(fila[n->sudo[i][j]-1] == 1)
               return 0;
         }
         fila[n->sudo[i][j]-1] = 1;
         
      }
      for(j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
            if(columna[n->sudo[i][j]-1] == 1)
               return 0;
            
         }
         columna[n->sudo[i][j]-1] = 1;
         
      }
      for(j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
            if(cuadro[n->sudo[i][j]-1] == 1){
               return 0;
            }
            
         }
         cuadro[n->sudo[i][j]-1] = 1;
      }
      for(j = 0; j < 9; j++){
         fila[j] = 0;
         columna[j] = 0;
         cuadro[j] = 0;
         
      }
      
   }
   return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(n->sudo[i][j]==0){
                int k;
                for(k=1;k<=9;k++){
                    Node* adj=copy(n);
                    adj->sudo[i][j]=k;
                    if(is_valid(adj)){
                        pushBack(list,adj);
                    }
                   
                }
            }
        }
    }
    return list;
}


int is_final(Node* n){
   int i, j;
   for(i=0; i<9 ; i++){
      for(j=0; j<9; j++){
         if(n->sudo[i][j] == 0)
            return 0;
      }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* s = createStack();
   push(s,initial);
   while(!is_empty(s)){
      Node* n = top(s);
      pop(s);
      if(is_final(n)){
         return n;
      }
      List* list = get_adj_nodes(n);
      Node* aux = first(list);
      while(aux){
         push(s,aux);
         aux = next(list);
      }
      free(n);
      (*cont)++;
   }
   
   return NULL;

}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/