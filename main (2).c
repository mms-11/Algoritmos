#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct NO {

  int num;
  struct NO * next;

}
NO;

typedef struct Grafo {

  struct NO * cabeca;
  struct NO * cauda;

  int grau;
  int valor;
  int representante;
}
Grafo;

typedef struct Fila {

  struct NO * head;
  struct NO * tail;

}
Fila;

Grafo adiciona_aresta(Grafo vertice, int valor_novo);
NO * desenfileira(NO * cabeca, NO * cauda);
NO * add_fila(NO * cabeca, NO * cauda, int v);
int distancia(Grafo * vertices, int qtd_vertices, int S, int referencia);
int Busca(Grafo Vertice, int v);
NO * remove_valor(Grafo * fila, int v);
Grafo list_insert(Grafo * fila, int v);
Grafo delete_list(Grafo * fila);
Grafo * Contracao(Grafo * adj, int A, int B, int vertices);

int main() {

  Grafo * adj;
  int tamanho_grafo, V, E, A, B, X, d, diferentes;
  char entrada[4];
  int * U;
  NO * aux;
  int grau,indice;
  scanf("%d %d", & V, & E);
  diferentes = V;

  adj = (Grafo * ) malloc(sizeof(Grafo) * V);
  if (adj == NULL) exit(-1);

  for (int i = 0; i < V; i++) {

    adj[i].cabeca = NULL;
    adj[i].cauda = NULL;
    adj[i].valor = i;
    adj[i].grau = 0;
    adj[i].representante = i;
  }

  for (int i = 0; i < E; i++) {
    scanf("%d %d", & A, & B);

    adj[A] = adiciona_aresta(adj[A], B);
    adj[A].grau++;

    adj[B] = adiciona_aresta(adj[B], A);
    adj[B].grau++;

  } //LISTA DE ADJACENCIA MONTADA

  /* for(int a = 0; a < V; a++){
     NO *aux;
    
     aux = adj[a].cabeca;
     printf(" GRAFO %d: ", a);
     while(aux != NULL){
    
     printf("(%d) ", aux->num);
     aux = aux->next;
    
    
   }
    
     printf("\n");
     }*/

  scanf("%d", & X);

  for (int i = 0; i < X; i++) {

    scanf(" %s", entrada);

    if (entrada[0] == 'D') {
indice =0;
      scanf("%d %d", & A, & B);
      d = distancia(adj, V, adj[A].representante, adj[B].representante);
      printf("%d\n", d);

    } else if (entrada[0] == 'C') {
      grau = 0;
      scanf("%d %d", & A, & B);
      if (adj[A].representante != adj[B].representante) {
        diferentes--;
      }
      adj = Contracao(adj, adj[A].representante, adj[B].representante, V);
      
      aux = adj[adj[A].representante].cabeca;
      while (aux != NULL) {
        if(adj[aux->num].representante != adj[A].representante  )
        grau++;
        aux = aux -> next;
      }
      
      adj[B].representante = adj[A].representante;
     
      printf("%d %d\n", diferentes, grau);

    }
  }

  return 0;

}

Grafo adiciona_aresta(Grafo vertice, int valor_novo) {

  NO * novo = (NO * ) malloc(sizeof(NO));

  novo -> num = valor_novo;
  novo -> next = NULL;

  if (vertice.cauda == NULL) { //SE A LISTA ESTIVER VAZIA
    vertice.cauda = novo;
    vertice.cabeca = novo;

  } else {
    vertice.cauda -> next = novo;
    vertice.cauda = novo;
  }

  return vertice;

}

int distancia(Grafo * vertices, int qtd_vertices, int S, int referencia) {
  int end = 0;
  int distancias[qtd_vertices];
  Grafo fila; //USAR SENTINELA
  fila.cabeca = (NO * ) malloc(sizeof(NO));
  fila.cabeca -> next = NULL;
  fila.cauda = fila.cabeca;

  fila = list_insert( & fila, S);

  for (int i = 0; i < qtd_vertices; i++) {
    distancias[i] = -1;

  }
  distancias[S] = 0;

  while (fila.cabeca != fila.cauda && end == 0) {
    NO * aux;
    int u, v;

    u = fila.cabeca -> next -> num;

    fila = delete_list( & fila);

    aux = vertices[u].cabeca;
    while (aux != NULL) {
      v = aux -> num;

      if (distancias[v] == -1) {
        distancias[v] = distancias[u] + 1;
        fila = list_insert( & fila, v);

      }
      if (v == referencia) {
        end = 1;
        return distancias[referencia];
      }
      aux = aux -> next;

    }

  }
  return distancias[referencia];

}
NO * desenfileira(NO * cabeca, NO * cauda) {
  NO * remove;
  if (cabeca != NULL) {
    remove = cabeca;
    cabeca = cabeca -> next;
    free(remove);

  } else if (cabeca == NULL) {
    cauda = cabeca;
  }

  return cabeca;
}
NO * add_fila(NO * cabeca, NO * cauda, int v) {
  //printf(" hdhdh");
  NO * novo = (NO * ) malloc(sizeof(NO));

  novo -> num = v;
  novo -> next = NULL;
  //printf(" bbb");

  if (cauda == NULL || cabeca == NULL) { //SE A LISTA ESTIVER VAZIA
    cabeca = novo;
    cauda = novo;
    //printf(" ccc");
  } else {
    cauda -> next = novo;
    cauda = novo;
  }

  return cabeca;
}
Grafo * Contracao(Grafo * adj, int A, int B, int vertices) {
  NO * LB;
  NO * LC;

 // printf(" A =%d B =%d\n ", A, B);
  //PROCURAR DE B ESTÁ EM A;

  LB = adj[B].cabeca;
  // printf("oi\n");
  //printf(" LB =%d\n", LB -> num);
  if (A != B) { //NAO ESTAO CONTRAIDOS

    while (LB != NULL) {
     // printf(" BUSCA DE %d= %d\n ", LB -> num, Busca(adj[A], LB -> num));
      if (Busca(adj[A], LB -> num) == 0) { //se a lista de A nao tiver os vertices de B
        adj[A] = adiciona_aresta(adj[A], LB -> num);
        adj[A].grau++;
      }
      LB = LB -> next;
    }
    
      adj[A].cabeca = remove_valor( & adj[A], B);
    
    //adj[B].representante = A; //COMPRESSAO DE CAMINHOS

    //adj[A].cabeca = remove_valor(&adj[A],B);

    //CHECAR SE EXISTEM 2 REPRESENTATES IGUAIS NA LISTA DE ADJACENCIA
    int iguais;
    for (int i = 0; i < vertices; i++) {
      iguais = 0;
      LC = adj[adj[i].representante].cabeca;

      if (adj[i].representante == B) { //atualizar o novo representante de i, pois o representante de B agora é RA
        adj[i].representante = A;
      }

      while (LC != NULL) {
        if (LC -> num == B) { //atualizar os vertices que antes eram B
          LC -> num = A;
        }

        if (LC -> num == A) { //nos iguais
          iguais++;
        }
        if (iguais == 2) {
          iguais = 0;
          adj[adj[i].representante].cabeca = remove_valor( & adj[adj[i].representante], A);
          LC = adj[adj[i].representante].cabeca;
        }

        LC = LC -> next;
      }
    }
  }
  return adj;

}

int Busca(Grafo Vertice, int v) {
  NO * aux;
  //printf("busca!\n");
  aux = Vertice.cabeca;
  //printf("%d\n", aux->num);
  int flag = 0;
  while (aux != NULL && flag == 0) {

    if (aux -> num == v) {
      flag = 1;
    } else {
      aux = aux -> next;
    }
  }
  return flag;
}
NO * remove_valor(Grafo * fila, int v) {
  NO * aux, * remove = NULL;
  aux = fila -> cabeca;
  int flag = 0;

  if (aux != NULL && aux -> num == v) {
    //achou o no que quer remover

    remove = fila -> cabeca;
    fila -> cabeca = fila -> cabeca -> next;
    free(remove);
    flag = 1;
  } else {
    while (aux != NULL && flag == 0) {
      if (aux -> next != NULL && aux -> next -> num == v) {
        flag = 1;
        remove = aux -> next;
        aux -> next = remove -> next;
        free(remove);

      } else {
        aux = aux -> next;
      }

    }
    if (fila -> cabeca == NULL) {
      fila -> cauda = fila -> cabeca;
    }
  }

  return fila -> cabeca;
}
Grafo list_insert(Grafo * fila, int v) {
  NO * novo;
  novo = (NO * ) malloc(sizeof(NO));
  novo -> next = NULL;
  novo -> num = v;
  fila -> cauda -> next = novo;
  fila -> cauda = novo;

  return *fila;
}

Grafo delete_list(Grafo * fila) {
  NO * remove = fila -> cabeca -> next;
  fila -> cabeca -> next = remove -> next;
  free(remove);
  if (fila -> cabeca -> next == NULL) {
    fila -> cauda = fila -> cabeca;
  }

  return *fila;
}