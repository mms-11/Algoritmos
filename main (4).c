#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

typedef struct Conexao {
  int T;
  unsigned C;

}
Conexao;

typedef struct Tabela {
  Conexao * conexao;
  int tamanhoUsado;
}
Tabela;

void QuickSort(Conexao * conexao, int L, int R);
int PivoEordenar(int L, int R, Conexao * conexao);
int BuscaBinaria(Conexao * conexao, int tamanhoLista, int procurado);
int FuncaoDispersao(int T, int M);

int main() {
  Tabela * tabela=NULL, * novaTabela=NULL;
  int M, carga = 0, indice, T, encontrado;
  unsigned C;
  float L, Lmax;
  char entrada[4];
  srand(time(NULL));
  
  //printf(" m e lmax\n ");
  scanf("%d %f", & M, & Lmax);
  
  //alocar tabela
  tabela = (Tabela * ) malloc(sizeof(Tabela) * M);
  if (tabela == NULL) {
    exit(-1);
  }
  //INICIALIZAR AS POSICOES
  for (int i = 0; i < M; i++) {
    tabela[i].conexao = (Conexao*)malloc(sizeof(Conexao));
    tabela[i].tamanhoUsado = 0;
    
  }
  
  //printf(" entrada \n");
  while (scanf(" %s", entrada) && strcmp(entrada, "END") != 0) {
      //printf("%s\n", entrada);
    carga = 0;
    if (strcmp(entrada, "NEW") == 0) { //NEW T C
      scanf("%d %u", &T, &C);
      //chacar se L<= Lmax
      for (int i = 0; i < M; i++) {
        if (tabela[i].conexao != NULL) carga = carga + tabela[i].tamanhoUsado;
      }
      L = (float) carga / M;
      //printf("carga =  %d e  L =%f", carga, L);
      if (L > Lmax) {
        //printf(" deu rehash1\n");
        novaTabela = (Tabela * ) malloc(sizeof(Tabela) * (2 * M + 1));
        if (novaTabela == NULL) {
          exit(-1);
        }
        //INICIALIZAR AS POSICOES
        for (int i = 0; i < (2 * M + 1); i++) {
          novaTabela[i].conexao = (Conexao*)malloc(sizeof(Conexao));
          novaTabela[i].tamanhoUsado = 0;
        }
        //printf(" NOVA TABELA INICIALIZADA\n");
        //ALOCAR E inserir elementos antigos na nova tabela
        //percorrer a antiga tabela
        for (int i = 0; i < M; i++) {
          for (int j = 0; j < tabela[i].tamanhoUsado; j++) {
            indice = FuncaoDispersao(tabela[i].conexao[j].T, 2 * M + 1);
            novaTabela[indice].conexao = (Conexao * ) realloc(novaTabela[indice].conexao, (novaTabela[indice].tamanhoUsado + 1) * (sizeof(Conexao)));
            if (novaTabela[indice].conexao == NULL){ 
                exit(-1);
            }
            //printf(" realloc DO VETOR DE %d OK\n", indice);
            //INSERIR
            novaTabela[indice].conexao[novaTabela[indice].tamanhoUsado].C = tabela[i].conexao[j].C;
            novaTabela[indice].conexao[novaTabela[indice].tamanhoUsado].T = tabela[i].conexao[j].T;
            novaTabela[indice].tamanhoUsado++;
            QuickSort(novaTabela[indice].conexao, 0, novaTabela[indice].tamanhoUsado);

           
            
            
          }
          // printf(" tamanho do vetor %d: %d\n", indice, novaTabela[indice].tamanhoUsado);
          free(tabela[i].conexao);
        }
        free(tabela);
        tabela = novaTabela;
        M = 2 * M + 1;
        novaTabela = NULL;

      }
      
      // NEW TC
      //funcao de dispersao
      indice = FuncaoDispersao(T, M);
      //adicionar no vetor de conexoes de mesmo indice
      tabela[indice].conexao = (Conexao *) realloc(tabela[indice].conexao, (sizeof(Conexao)) * tabela[indice].tamanhoUsado + 1);
      //printf(" realloc 2 ok\n");
      if (tabela[indice].conexao == NULL){
        exit(-1);  
      }
      //inserir os dados da nova conexao
      tabela[indice].conexao[tabela[indice].tamanhoUsado].C = C;
      tabela[indice].conexao[tabela[indice].tamanhoUsado].T = T;
      tabela[indice].tamanhoUsado++;
       //QuickSort(tabela[indice].conexao, 0, tabela[indice].tamanhoUsado-1);

      //ordenar o vetor de indice indice com base nos time stamps
      //QuickSort(tabela[indice].conexao, 0, tabela[indice].tamanhoUsado);
      printf("%d %d\n", indice, tabela[indice].tamanhoUsado);

    } //FIM DO NEW************
    if (strcmp(entrada, "QRY") == 0) {
      //printf(" t ");
      scanf("%d", &T);
      //printf(" T = %d", T);
      indice = FuncaoDispersao(T, M);
      encontrado = BuscaBinaria(tabela[indice].conexao, tabela[indice].tamanhoUsado, T);
      if (encontrado != -1) {
        printf("%u %d\n", tabela[indice].conexao[encontrado].C, encontrado);
      } else {
        printf("-1 -1\n");
      }
    }
   // printf(" entrada\n");
  }
  for (int i = 0; i < M; i++) {
    //printf("Index %d\n", i);
    for(int j = 0; j < tabela[i].tamanhoUsado; j++){
        //printf("T %d: %d\nIP: %llu", j, tabela[i].conexao[j].T, tabela[i].conexao[j].C);
    }
    //printf("\n");
    free(tabela[i].conexao);
  }
  free(tabela);
  return 0;
}

//***********

void QuickSort(Conexao * conexao, int L, int R) {
  int pivo;
  if (R - L > 1) {
    pivo = PivoEordenar(L, R, conexao);
    QuickSort(conexao, L, pivo);
    QuickSort(conexao, pivo + 1, R);
  }

}
int PivoEordenar(int L, int R, Conexao * conexao) {
  int limite = R - L; //limite do numero aleatorio
  //gerar um numero aleatorio
  int P = ((rand() % limite)+ L);
  int a = L, b = R - 1;
  //dividir o vetor
  Conexao aux;
  aux = conexao[L];
  conexao[L] = conexao[P];
  conexao[P] = aux;
  while (a <= b) {
    while (conexao[a].T <= conexao[L].T && a < R) {
      a++;
    }
    while (conexao[b].T > conexao[L].T && b > L) {
      b--;
    }
    if (a < b) { //trocar de posicao, ordenar a particao
      aux = conexao[a];
      conexao[a] = conexao[b];
      conexao[b] = aux;
    }
  }
  //continuar a particao
  //atualizar o valor do pivo
  aux = conexao[L];
  conexao[L] = conexao[b];
  conexao[b] = aux;

  return b;
}
int BuscaBinaria(Conexao * conexao, int tamanhoLista, int procurado) {
  int i = 0, j = tamanhoLista - 1, central;

  Conexao aux;
  while (i <= j) {
    central = (i + j) / 2;
    if (conexao[central].T == procurado) {
      return central;
    } else if (conexao[central].T < procurado) {
      i = central + 1;
    } else {
      j = central - 1;
    }
  }
  return -1;

}
int FuncaoDispersao(int T, int M) {
  return T % M;
}