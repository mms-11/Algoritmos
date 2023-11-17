#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct NO {
  struct NO * right;
  struct NO * left;
  int num;

  //mudanca de altura
}
NO;

NO * insere(NO * root, int num, int * profundidade);
NO * RotateLeft(NO * root);
NO * RotateRight(NO * root);
NO * Busca(NO * root, int valor_procurado, int * profundidade, int * flag);
NO * Delete(NO * root, int valor_deletado, int * profundidade, int * pai, int * flag,int *son);
NO * DeleteMin(NO * root, int * AUX);
int splay(int * profundidade, NO * root, int num);
NO * AcharPai(NO * root, int num);
NO * Splay(NO * root, int * profundidade, NO * node, int num);
NO * AcharProfundidade(NO * root, int * profundidadeT, int x, int * P);

int main() {
  char entrada[5];
  int X, flag = 0;
  int D;
  NO * raiz = NULL;
  NO * aux;
  int pai,filho;
  int P = 0;

  while (scanf(" %s", entrada) && strcmp(entrada, "END") != 0) {
    D = 0;
    flag = 0;
    if (entrada[0] == 'I') { //INSERE

      scanf("%d", & X);
      raiz = insere(raiz, X, & D);

      printf("%d\n", D);
    }
    if (entrada[0] == 'F') {
      scanf("%d", & X);
      raiz = Busca(raiz, X, & D, & flag);
      printf("%d\n", D);
    }
    if (entrada[0] == 'D') {
      scanf("%d", & X);

      raiz = Delete(raiz, X, & D, & pai, & flag,&filho);
      printf("%d\n", D);

    }

  }

  return 0;

}
NO * insere(NO * root, int num, int * profundidade) {
  if (root == NULL) {
    NO * novo = (NO * ) malloc(sizeof(NO));
    if (novo == NULL) exit(1);

    novo -> num = num;

    novo -> right = NULL;
    novo -> left = NULL;

    return novo;

  }
  if (num < root -> num) {
    ( * profundidade) ++;
    root -> left = insere(root -> left, num, profundidade);
    root = RotateRight(root);

    return root;
  } else if (num > root -> num) {
    ( * profundidade) ++;
    root -> right = insere(root -> right, num, profundidade);
    root = RotateLeft(root);

    return root;
  } else if (num == root -> num) {
    return root;
  }

}
NO * RotateLeft(NO * root) {
  NO * R = NULL;
  NO * RL = NULL;
  R = root -> right;
  RL = R -> left;
  R -> left = root;
  root -> right = RL;

  return R;
}
NO * RotateRight(NO * root) {
  NO * L = NULL, * LR = NULL;
  L = root -> left;
  LR = L -> right;
  L -> right = root;
  root -> left = LR;

  return L;
}
NO * Busca(NO * root, int valor_procurado, int * profundidade, int * flag) {

  if (root == NULL) {
    * flag = 1;
    return NULL;
  }

  if (root -> num == valor_procurado) {
    return root;
  } else if (valor_procurado < root -> num) {
    ( * profundidade) ++;
    root -> left = Busca(root -> left, valor_procurado, profundidade, flag);
    if ( * flag != 1) root = RotateRight(root);
  } else if (valor_procurado > root -> num) {
    ( * profundidade) ++;
    root -> right = Busca(root -> right, valor_procurado, profundidade, flag);
    if ( * flag != 1) root = RotateLeft(root);
  }

  return root;

}

NO * Delete(NO * root, int valor_deletado, int * profundidade, int * pai, int * flag,int *son) {
   NO * aux ;
  NO * aux2;
  
  if (root == NULL) {
    * flag = 1;

    return NULL;
  }
  
  
  
  else if (valor_deletado < root -> num) { 
    ( * profundidade) ++;
    root -> left = Delete(root -> left, valor_deletado, profundidade, pai, flag, son);
    
    if (root -> left == NULL || root -> left -> num == *son) {
      * pai = root -> num;
    }
    
    else if (* flag == 0) {
      root = RotateRight(root);
    }
    return root;
  }
   
  
  else if (valor_deletado > root -> num) {
    ( * profundidade) ++;
     root -> right = Delete(root -> right, valor_deletado, profundidade, pai, flag, son);

    
    if (root -> right == NULL || root -> right -> num == * son) {
      * pai = root -> num;
    }
    
    else if ( * flag == 0) {
      root = RotateLeft(root);
    }
    return root;
  } 
  
  else if (valor_deletado == root -> num) { //valor_deletado = num

    if (root -> left == NULL) { //caso 1 filho

      aux = root -> right;
      if (aux != NULL) {
                *son = aux->num;
            }
     

      return aux;
    }
    
    else if (root -> right == NULL) { //caso 1 filho

      aux2 = root -> left;
      if (aux2 != NULL) {
                *son = aux2->num;
            }
      
      return aux2;
    }
    else {
      if(root->right!=NULL){
        root -> right = DeleteMin(root -> right, & root -> num);
      *son=root->num;
      }
      
      return root;
    }

  }

}
NO * DeleteMin(NO * root, int * AUX) {

  NO * r = NULL;
  NO * l = NULL;
  int filho;

  if (root -> left == NULL) {

    r = root -> right;
    filho = root -> num;
    free(root);
    *AUX = filho;
    
    return r;
  }
  else {
    l = DeleteMin(root -> left, AUX);
    root -> left = l;
    return root;
  }

}