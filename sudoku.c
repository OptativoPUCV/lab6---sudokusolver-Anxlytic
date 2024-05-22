#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct {
   int sudo[9][9];
} Node;

Node* createNode() {
  Node* n = (Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n) {
    Node* new = (Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file(char* file_name) {
  Node* n = createNode();
  FILE* file = fopen(file_name, "r");
  int fila, col;
  for(fila = 0; fila < 9; fila++) {
       for(col = 0; col < 9; col++) {
          if(!fscanf(file, "%d", &n->sudo[fila][col]))
            printf("failed to read data!");
       }
  }

  fclose(file);
  return n;
}

void print_node(Node* n) {
    int fila, col;
    for(fila = 0; fila < 9; fila++) {
       for(col = 0; col < 9; col++)
          printf("%d ", n->sudo[fila][col]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
   int fila, col, subFila, subCol;

   for (fila = 0; fila < 9; fila++) {
       int numFila[10] = {0};
       for (col = 0; col < 9; col++) {
          if (n->sudo[fila][col] != 0 && numFila[n->sudo[fila][col]] == 1) {
             return 0; 
          } else {
             numFila[n->sudo[fila][col]] = 1;
          }
       }
   }

   for (col = 0; col < 9; col++) {
      int numCol[10] = {0};
      for (fila = 0; fila < 9; fila++) {
         if (n->sudo[fila][col] != 0 && numCol[n->sudo[fila][col]] == 1) {
            return 0; 
         } else {
            numCol[n->sudo[fila][col]] = 1;
         }
      }
   }

   for (fila = 0; fila < 9; fila += 3) {
      for (col = 0; col < 9; col += 3) {
         int numBox[10] = {0};
         for (subFila = fila; subFila < fila + 3; subFila++) {
            for (subCol = col; subCol < col + 3; subCol++) {
               if (n->sudo[subFila][subCol] != 0 && numBox[n->sudo[subFila][subCol]] == 1) {
                  return 0;
               } else {
                  numBox[n->sudo[subFila][subCol]] = 1;
               }
            }
         }
      }
   }

   return 1;
}

List* get_adj_nodes(Node* n) {
   List* adjList = createList();
   int number = 1;
   int foundEmpty = 0;

   for(int fila = 0; fila < 9; fila++) {
      for(int col = 0; col < 9; col++) {
         if(n->sudo[fila][col] == 0) {
            foundEmpty = 1;
            for(int i = 0; i < 9; i++, number++) {
               Node* newNode = copy(n);
               newNode->sudo[fila][col] = number;
               if(is_valid(newNode) == 1) {
                  pushBack(adjList, newNode);
               }
            }
         }
         if(foundEmpty) break;
      }
      if(foundEmpty) break;
   }   
   return adjList;
}

int is_final(Node* n) {
   for(int fila = 0; fila < 9; fila++) {
      for(int col = 0; col < 9; col++) {
         if(n->sudo[fila][col] == 0) {
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont) {
   Stack* stackNodes = createStack();
   push(stackNodes, initial);

   while(top(stackNodes) != NULL) {
      Node* currentNode = top(stackNodes); (*cont)++;
      pop(stackNodes);

      if(is_final(currentNode)) return currentNode;

      List* adjList = get_adj_nodes(currentNode);
      Node* adjNode = first(adjList);

      while(adjNode) {
         push(stackNodes, adjNode);
         adjNode = next(adjList);
      }
      free(currentNode);
   }
   free(stackNodes);
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