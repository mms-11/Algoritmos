#include <stdio.h>

#include <stdlib.h>

typedef struct Carta {
  int valor;
  char Naipe;
  struct Carta * proximo;
}
Carta;

typedef struct Jogador {

  Carta * cabecaF;
  Carta * caldaF;

  int Qtd_Cartas;
  int eliminado;//FLAG
}
Jogador;

typedef struct PILHA {
  Carta * topo;
  int TamanhoCuscuz;
}
PILHA;

int acharVencedor(Jogador * players, int qtdPlayers);
int GameOver(Jogador * players, int qtdPlayers);
Jogador comerCuscuz(Jogador winner, PILHA * stack);
int vencedorRodada(Jogador * players, int qtdPlayers);
PILHA * removeCarta(Jogador * player, PILHA * stack);
Jogador addCarta(Jogador player, int valor, char naipe);

int main() {
  int qtdJogadores, i = 0, j = 0, Valor = 0, flagFim = 0, Rodada = 0, vencedor;
  char evento[1000], Naipe;

  //printf("digite a quantidade de jogadores no jogo; ");
  scanf("%d", & qtdJogadores);

  //alocar ponteiro para jogadores
  Jogador * jogador = (Jogador * ) malloc(qtdJogadores * sizeof(Jogador));
  if (jogador == NULL) exit(1);

  //iniciar a fila de cada jogador
  for (i = 0; i < qtdJogadores; i++) {
    
    jogador[i].cabecaF = jogador[i]. caldaF = NULL;
    jogador[i].eliminado = jogador[i].Qtd_Cartas = 0;
  }
  //COMECAR O JOGO
  //printf("digite o evento: ");
  while ((flagFim == 0) && (scanf(" %s", evento) != EOF)) {
    //EVENTO DEAL
    if (evento[0] == 'D') {
      //adicionar cartas dos jogadores
      for (i = 0; i < qtdJogadores; i++) {
        if (jogador[i].eliminado == 0) {
          //printf("digite a carta: ");
          scanf("%d%c", & Valor, & Naipe);
          jogador[i] = addCarta(jogador[i], Valor, Naipe);
          jogador[i].Qtd_Cartas++;
        }

      }
    }

    if (evento[0] == 'R') {
      vencedor = -1;

      PILHA * pilha = (PILHA * ) malloc(sizeof(PILHA));
      if (pilha == NULL) exit(1);
      pilha -> topo = NULL; //PILHA VAZIA
      pilha -> TamanhoCuscuz = 0;

      while (vencedor == -1) {

        //checar se existem jogadores disponiveis
        flagFim = GameOver(jogador, qtdJogadores);
        if (flagFim == 1) {
          printf("-1 -1 -1\n");
        }
        vencedor = vencedorRodada(jogador, qtdJogadores);
        //retirar a carta dos jogadores e empilhar no cuscuz
        for (i = 0; i < qtdJogadores; i++) {
          if (jogador[i].eliminado == 0) {
            pilha = removeCarta( & jogador[i], pilha);
            pilha -> TamanhoCuscuz++;
            jogador[i].Qtd_Cartas--;
          }
        }

        if (vencedor != -1) {
          //vencedor come o cuscuz
          jogador[vencedor] = comerCuscuz(jogador[vencedor], pilha);
          printf("%d %d %d\n", Rodada, vencedor, pilha -> TamanhoCuscuz);
          Rodada++;
        }
        //Rodada++;
      }
      free(pilha);
    }
    if (evento[0] == 'E') {
      //PROCURAR O JOGADOR QUE TIVER MAIS CARTAS
      vencedor = acharVencedor(jogador, qtdJogadores);
      if (vencedor != -1) {
        printf("%d\n", vencedor);
      } else {
        printf("-1\n");
      }
    }
  }
  for (i = 0; i < qtdJogadores; i++) {
    if (jogador[i].eliminado == 0)
      while (jogador[i].cabecaF != NULL) {
        Carta * tmp = jogador[i].cabecaF;
        jogador[i].cabecaF = jogador[i].cabecaF -> proximo;
        free(tmp);
      }
  }
  free(jogador);

  return 0;
}
//**********************************************************
Jogador addCarta(Jogador player, int valor, char naipe) {
  Carta * nova = (Carta * ) malloc(sizeof(Carta));
  nova -> Naipe = naipe;
  nova -> valor = valor;
  nova -> proximo = NULL;
  //se a lista estiver vazia
  if (player.caldaF == NULL) {
    player.caldaF = nova;
    player.cabecaF = nova;
  } else {
    player.caldaF -> proximo = nova;
    player.caldaF = nova;
  }
  //player.Qtd_Cartas++;
  return player;

}
//********************************************************
PILHA * removeCarta(Jogador * player, PILHA * stack) {
  //remover primeira carta de cada jogador e adicionar na pilha(cuscuz)
  if (player -> cabecaF != NULL) {
    Carta * tmp = player -> cabecaF;
    player -> cabecaF = player -> cabecaF -> proximo;
    //player->Qtd_Cartas--;

    //adicionar tmp na pilha
    //o antigo topo é apontado pela carta tmp
    tmp -> proximo = stack -> topo;
    //o novo topo passa a ser tmp
    stack -> topo = tmp;
  }
  if (player -> cabecaF == NULL) {
    player -> eliminado = 1;
  }
  return stack;
} //*****************************************************
int vencedorRodada(Jogador * players, int qtdPlayers) {
  Carta * tmp = (Carta * ) malloc(sizeof(Carta));
  if (tmp == NULL) exit(1);

  tmp -> Naipe = 'C';
  tmp -> valor = 0;
  tmp -> proximo = NULL;
  Carta * maior = tmp;
  int vencedor = -1;

  for (int i = 0; i < qtdPlayers; i++) {
    if (players[i].eliminado == 0 && players[i].cabecaF -> valor > maior -> valor) {
      maior = players[i].cabecaF;
      vencedor = i;
    } else if (players[i].eliminado == 0 && players[i].cabecaF -> valor == maior -> valor) {
      if (players[i].cabecaF -> Naipe > maior -> Naipe) {
        maior = players[i].cabecaF;
        vencedor = i;
      } else if (players[i].cabecaF -> Naipe == maior -> Naipe)
        vencedor = -1; //deu empate

    }
  }

  free(tmp);
  return vencedor;
} //********************************************************************************************
Jogador comerCuscuz(Jogador winner, PILHA * stack) {
  //fazer o vencedor comer o cuscuz
  // se o jogador estiver com zero cartas,atualizar o seu unico no com a primeira carta do topo
  if (winner.Qtd_Cartas == 0) {
    winner.caldaF = stack -> topo;
     winner.cabecaF = stack -> topo;
    winner.eliminado = 0;
  } else {
    winner.caldaF -> proximo = stack -> topo;
  }
  Carta * tmp = stack -> topo;
  while (tmp -> proximo != NULL) {
    tmp = tmp -> proximo;
  } //atualizar a nova calda da fila do vencedor
  winner.caldaF = tmp;
  winner.Qtd_Cartas += stack -> TamanhoCuscuz;
  return winner;
} //***********************************************************************************************
int acharVencedor(Jogador * players, int qtdPlayers) {
  int maior = 0, vencedor = -1;

  for (int i = 0; i < qtdPlayers; i++) {
    if (players[i].eliminado == 0 && players[i].Qtd_Cartas > maior) {
      maior = players[i].Qtd_Cartas;
      vencedor = i;
    } else if (players[i].eliminado == 0 && players[i].Qtd_Cartas == maior)
      vencedor = -1;
  }

  return vencedor;

} //*******************************************************************************************************
int GameOver(Jogador * players, int qtdPlayers) {
  //ver se ainda existam jogadores com cartas
  int contE = 0, contNE = 0, GameOver = 0;
  for (int i = 0; i < qtdPlayers; i++) {
    if (players[i].eliminado == 0) {
      contNE++;
    } else if (players[i].eliminado == 1) {
      contE++;
    }
  }
  if (contE == qtdPlayers) {
    return 1;
  } else {
    return 0;
  }
}