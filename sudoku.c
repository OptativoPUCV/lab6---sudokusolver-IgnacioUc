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
   int i, j, k, l, val;
   int fila[9], columna[9], cuadro[9];

   // Validar filas y columnas
   for (i = 0; i < 9; i++) {
      memset(fila, 0, sizeof(fila));
      memset(columna, 0, sizeof(columna));
      for (j = 0; j < 9; j++) {
         // Validar fila
         if ((val = n->sudo[i][j]) != 0) {
            if (fila[val - 1]++) return 0;
         }
         // Validar columna
         if ((val = n->sudo[j][i]) != 0) {
            if (columna[val - 1]++) return 0;
         }
      }
   }

   // Validar subcuadrículas
   for (i = 0; i < 9; i += 3) {
      for (j = 0; j < 9; j += 3) {
         memset(cuadro, 0, sizeof(cuadro));
         for (k = 0; k < 3; k++) {
            for (l = 0; l < 3; l++) {
               if ((val = n->sudo[i + k][j + l]) != 0) {
                  if (cuadro[val - 1]++) return 0;
               }
            }
         }
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
               return list;
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