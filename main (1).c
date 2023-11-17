#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO {

int num;
struct NO *next;
int entrega;
int espera;
 //int *peso; //vetor para peso de cada aresta

}NO;

typedef struct Grafo{

 int *pesos;
 struct NO *cabeca;
 struct NO *cauda;
 int qtd_vertices;
 int qtd_arestas;
 int grau;
 int valor;

}Grafo;

typedef struct Fila_Pedidos {

 int id;
 int entrega;
 struct NO *head;
 struct NO *tail;
 int espera;

}Fila_Pedidos;

typedef struct heap{

int distancia;//peso
int local;

}heap;

typedef struct restaurante{
int *distancias; //vetor para as distancias dos restaurantes
int localidade;
}restaurante;

Grafo add(Grafo vertice, int valor_novo, int peso);
Fila_Pedidos add_pedido(Fila_Pedidos fila, int entrega, int id);
int *Distancia(Grafo *adj,int S,int vertices); //vertices = quantidade de vertices
heap *heap_insert(heap *H, int distancia, int destino,int *tamanhoAtual, int *tamanhoMax);
heap *bubble_up(heap *H, int p);
int heap_extract(heap *H, int *distancia, int *tamanhoAtual);
heap *bubble_down(heap *H, int b,int p);
int contador_pendentes(Fila_Pedidos fila);
int existe(heap *H, int v,int tamanho);
NO *cancelar_pedido(Fila_Pedidos *fila, int v);
NO *entregar_pedido(Fila_Pedidos *fila);
int main() {

  int V,E,N,M, X, Y,A,B,L,I,D, K,Z,pendentes = 0;
  int Localidade;
  Grafo *adj;
  Fila_Pedidos fila;
  //int *restaurantes;
  char entrada[4];
  restaurante *Restaurantes;
 int caminho;
  NO *paux;
  int flag = 0;
 

//*******************************************************
 /* fila.head=(NO*)malloc(sizeof(NO));//SENTINELA
  fila.tail = fila.head;
  fila.head->next = NULL;
  */
  scanf("%d %d %d %d", &V, &E, &N, &M);
 
 int *entregador;
 entregador = (int*)malloc(M*sizeof(int));
  
  adj =(Grafo*)malloc(sizeof(Grafo)*V);
   if(adj == NULL) exit(-1);
   adj->qtd_arestas = E;
   adj->qtd_vertices = V;
 
  Restaurantes = (restaurante*)malloc(sizeof(restaurante)*N);
   if( Restaurantes == NULL)  exit(-1);
 
 
  fila.head = NULL;
  fila.tail = NULL;
 
 

  for(int i =0; i < V; i++){
   
    adj[i].cabeca = NULL;
    adj[i].cauda = NULL;
    adj[i].valor = i;
    adj[i].pesos=(int*)malloc(V* sizeof(int));
    adj[i].grau= 0;

    if(adj[i].pesos == NULL) exit(-1);
   
  }

  for(int i =0; i < E; i++){
    
    scanf("%d %d %d", &A, &B, &L);
   
    adj[A] = add(adj[A], B, L);
    adj[A].grau++;
    
   
    adj[B] = add(adj[B], A, L);
    adj[B].grau++;
  
   
    }
   
 /*printf(" os nós de %d são: ", A);
    while(aux1 != NULL){
     
      printf("%d ", aux1->num);
      aux1 = aux1->next;
    }
    printf("\n");
   
printf(" os nós DE %d são: ", B);
    while(aux2 != NULL){
     
      printf("%d ", aux2->num);
      aux2 = aux2->next;
    }
    printf("\n");
   // printf(" a cabeca de A = %d\n a cabeca de B = %d\n", adj[A].cabeca->num, adj[B].cabeca->num);
  }
*/
    /*int m =0;
    for(int a = 0; a < V; a++){
      NO *aux;
     
      aux = adj[a].cabeca;
      printf(" GRAFO %d: ", a);
      while(aux != NULL){
     
      printf("(%d,%d) ", aux->num, adj[a].pesos[aux->num]);
      aux = aux->next;
     
     
    }
      m=0;
      printf("\n");
    }
   */
  for(int i = 0; i < N; i++){
   
    scanf("%d", &Localidade);
    //printf(" local %d\n", Localidade);
   
    Restaurantes[i].localidade = Localidade;
   
  Restaurantes[i].distancias =  Distancia(adj, Restaurantes[i].localidade,V);
    if(flag == 0){
      for(int k =0; k <M; k++){
    entregador[k] = Localidade;
        
  }
      flag =1;
    }
    //printf("driksta ok\n");
   
//printf(" Distancia de %d\n ", i);
   
    /*for(int j = 0; j < V; j++){
      printf("%d ", Restaurantes[i].distancias[j]);
    }*/

   //printf("\n \n");
  }

  while(strcmp(entrada,"END") != 0){
    scanf(" %s", entrada);
    if(entrada[0] == 'N'){//EVENTO NEW, adicionar novo pedido
     
      scanf("%d %d", &I, &Z);
      fila = add_pedido(fila,  Z, I);
     // printf(" AAA");
      //tentar entregar
      pendentes = contador_pendentes(fila);

     printf("+%d %d\n", I, pendentes);
     
    }
    else if(entrada[0] == 'C'){
      scanf("%d", &I);

      fila.head = cancelar_pedido(&fila, I);
      //paux = fila.head;
     // while(paux != NULL){
        //printf(" o proximo da fila = %d\n", paux->num);
      //  paux = paux->next;
    //  }
      pendentes = contador_pendentes(fila);
      printf("-%d %d\n", I, pendentes);
    }
    else if(entrada[0] == 'D'){//delivery
      scanf("%d",&D); //indice do entregador
      //printf("o ID do proximp pedido = %d",fila.head->num);
      I = fila.head->num; //id do pedido
      X = entregador[D];
     
      Z = fila.head->entrega;
      K = 929929;
      for(int i =0; i < N; i++){
        caminho = Restaurantes[i].distancias[X] + Restaurantes[i].distancias[Z];
        //infinito
        if(  caminho < K ){
          K = caminho;
          Y = Restaurantes[i].localidade;
        }
      }
      printf("%d %d %d %d %d\n", I, X, Y, Z, K);
      entregador[D] = Z;
      //fila.head = entregar_pedido(&fila);
      fila.head = cancelar_pedido(&fila, I);
     //printf("proximo pedido = %d\n", fila.head->num);
    }
   /* NO* auxiliar = fila.head;
    int contador = 0;
    while(auxiliar != NULL){
     
       printf(" pedido %d = %d\n", contador, auxiliar->num);
      contador++;
      auxiliar = auxiliar->next;
    }*/
  }
 
 free(entregador);
 
  return 0;
}
Grafo add(Grafo vertice, int valor_novo, int peso){
 
  NO *novo = (NO*)malloc(sizeof(NO));
 
    novo->num=valor_novo;
    novo->next=NULL;
 
  if(vertice.cauda == NULL){//SE A LISTA ESTIVER VAZIA
    vertice.cauda=novo;
    vertice.cabeca=novo;
   
  }else{
    vertice.cauda->next=novo;
    vertice.cauda=novo;
  }
 
  vertice.pesos[valor_novo] = peso;
 
  return vertice;
     
}

Fila_Pedidos add_pedido(Fila_Pedidos fila, int entrega, int id){
  //printf(" hdhdh");
  NO *novo = (NO*)malloc(sizeof(NO));
 
  novo->num=id;
  novo->entrega=entrega;
  novo->espera = 1; //flag
  novo->next=NULL;
  //printf(" bbb");
 
 
  if(fila.tail == NULL || fila.head == NULL ){//SE A LISTA ESTIVER VAZIA
    fila.head=novo;
    fila.tail=novo;
    //printf(" ccc");
  }else{
   fila.tail->next=novo;
    fila.tail=novo;
  }
 
 
 
  return fila;
}
int *Distancia(Grafo *adj,int S, int vertices){

  int tamanhoMax = 1;
  int tamanhoAtual = 0;
   
  int d,v,u,w,peso,indicador = -1; // d = PESO;
  NO *e;
  heap *H;
 
  int *D;
  D = (int*)malloc(vertices*sizeof(int));//vetor de distancias do restaurante
  if(D == NULL)  exit(-1);
 
 
  H= (heap*)malloc(sizeof(heap));
  if(H == NULL) exit(-1);
 
 
 
  for (int i = 0; i < vertices; i++) {
   
        D[i] = -1;
    }
  D[S] = 0;

  H = heap_insert(H, 0, S,&tamanhoAtual, &tamanhoMax);//vetor,peso e loocalidade

  for(int i =0; i < vertices; i++){
   
   
    u = heap_extract(H, &d, &tamanhoAtual);
    //printf(" valor extraido da Heap = %d\n", u);
   
    e = adj[u].cabeca;
 
    while(e != NULL){
     
      v = e->num;
      //printf(" vertice ligado a %d = %d\n", u, v);
      peso = adj[u].pesos[v];
      //printf(" peso dessa aresta = %d\n", peso);
     
      if( d + peso < D[v] || D[v] == -1){
        D[v] = d + peso;
        //HEAP UPDATE
        indicador = -1;
        indicador = existe(H,v,tamanhoAtual);
      //printf(" indicador = %d\n ", v);
        if(indicador != -1){// valor existe
          //atualizar distancia
          H[indicador].distancia = D[v];
         H = bubble_up(H,indicador);
          //printf(" Deu bubble UP!\n");
          
         //printf("%d e o peso de H[%d] = %d\n",tamanhoAtual, indicador, H[indicador].distancia);
       
        }
        if(indicador == -1){
          H = heap_insert(H, D[v], v,&tamanhoAtual, &tamanhoMax);
           //printf("NAO  Deu bubble UP!\n");
          //printf("tamanho da heap = %d e o peso de H[%d] = %d\n",tamanhoAtual, v, H[v].distancia);
        }//printf("HEAP\n");
       /*for(int i =0; i < tamanhoAtual; i++){
         printf("  %d = (%d,%d)\n ", i, H[i].local, H[i].distancia );
       }*/
        
        //printf("\n");
      }
      e = e->next;
    }
   
  }
 return D;
}
heap *heap_insert(heap *H, int distancia, int destino,int *tamanhoAtual, int *tamanhoMax){

  if(*tamanhoAtual == *tamanhoMax){
   
     *tamanhoMax = 2 * (*tamanhoAtual);
    H = (heap*)realloc( H,(*tamanhoMax)*sizeof(heap));
    if( H == NULL) exit(-1);
   
  }
   H[*tamanhoAtual].local = destino;
    H[*tamanhoAtual].distancia = distancia;
   H = bubble_up(H, *tamanhoAtual);
    (*tamanhoAtual)++;

    return H;
}
heap *bubble_up(heap *H, int p){

heap aux;
 
  while(p > 0 &&  H[p].distancia <=  H[(p-1)/2].distancia){
   
    aux =  H[p];
     H[p] = H[(p-1)/2];
     H[(p-1)/2] = aux;

    p = (p-1)/2;
  }
  return  H;
}

int heap_extract(heap *H, int *distancia, int *tamanhoAtual){
  heap R;
  heap aux;

  R =  H[0];
 
 
 if(*tamanhoAtual > 0){
   
   aux = H[0];
   H[0] = H[(*tamanhoAtual)-1];
    H[(*tamanhoAtual)-1]= aux;
    (*tamanhoAtual)--;
    H = bubble_down(H, 0,*tamanhoAtual);
 }

  *distancia = R.distancia;

  return R.local;
 
}

heap *bubble_down(heap *H, int b,int tamanho){
  int l = 2*b +1;
  int r = 2*b +2;
  int  m = b;
 
  heap aux;

  if( l < tamanho && H[l].distancia <= H[m].distancia){
    m = l;
  }
  if(r < tamanho && H[r].distancia <= H[m].distancia){
    m = r;
  }
  if(m != b){
    aux = H[m];
    H[m] = H[b];
    H[b] = aux;
   
    return bubble_down(H,m,tamanho);
  }

  return H;
}
int contador_pendentes(Fila_Pedidos fila){
  NO *aux = fila.head;
  int contador = 0;
  while(aux != NULL){
    
      contador++;
    
    aux = aux->next;
  }
  return contador;
}
int existe(heap *H, int v,int tamanho){
 
int i =0;
int aux = -1;
 
  while(aux == -1 && i < tamanho ){
   
    if(H[i].local == v){
      //flag = 1;
      aux = i;
    }
   
    i++;
  }
  return aux;
}

NO* cancelar_pedido(Fila_Pedidos *fila, int v){
  NO *aux, *remove = NULL;
  aux = fila->head;
  int flag = 0;

 
    if( aux != NULL && aux->num == v ){
      //achou o no que quer remover
     
      remove = fila->head;
      fila->head = fila->head->next;
      free(remove);
      flag =1;
    } else {
      while(aux != NULL && flag == 0){
        if(aux->next != NULL && aux->next->num == v){
          flag =1;
          remove = aux->next;
          aux ->next = remove->next;
          free(remove);
         
        }else{
          aux = aux->next;
        }
       
      }
       if(fila->head == NULL){
         fila->tail = fila->head;
       }
    }
   
 
  return fila->head;
}

NO* entregar_pedido(Fila_Pedidos *fila){
  NO *remove;
  if(fila->head != NULL){
    remove = fila->head;
  fila->head = fila->head->next;
  free(remove);
  
  }else if(fila->head == NULL){
    fila->tail = fila->head;
  }
    
  
 
  return fila->head;
}
