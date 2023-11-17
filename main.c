#include <stdio.h>

typedef struct flag{
int infinito;
int val;
}flag;

int main(void) {
  int n, m,d,contador = 0;
  
  while( scanf("%d %d", &n,&m) != EOF){
    contador = 0;
    int S[m+1][n+1];
  
int V[n];
int C[m];
  
  for(int i = 0; i < n; i++){
    scanf("%d", &V[i]);
    
  }
  
  for(int i = 0; i < m; i++){
    scanf("%d", &C[i]);
    
  }
  for(int i =0; i < m+1; i++){
    for(int j =0; j < n+1; j++){

      if( i == 0 || j == 0 || j<i){
        S[i][j] = -__INT_MAX__;
      }
      else{
        if(S[i-1][j-1] == -__INT_MAX__ && S[i][j-1] == -__INT_MAX__){
          S[i][j] = C[i-1]*V[j-1];
        }
        else if(S[i-1][j-1] == -__INT_MAX__){
          
          if(S[i][j-1] > C[i-1]*V[j-1]){
             S[i][j] = S[i][j-1];
          }
          else{
            S[i][j]= C[i-1]*V[j-1];
          }
          
        }
        else if(S[i][j-1] == -__INT_MAX__){
            S[i][j]= C[i-1]*V[j-1] + S[i-1][j-1];
        }
        else {
          if(S[i][j-1] > C[i-1]*V[j-1] + S[i-1][j-1]){
            S[i][j] = S[i][j-1] ;
          }
          else{
             S[i][j] = C[i-1]*V[j-1] + S[i-1][j-1];
          }
        }
      }
      
      
    }
   
  }
//for(int i =0; i < m+1; i++){
    //for(int j =0; j < n+1; j++){
      //printf("%d ", S[i][j]);
    //}
  //printf("\n");
  //}
  int indices[m];
  int aux = m;
  for(int i = n; i >=0;i-- ){
    
    if(S[aux][i-1] != S[aux][i] && aux != 0){
      indices[aux-1] = i-1;
      aux --;
    }
    
  }

  printf("%d\n", S[m][n]);

    
for(int i = 0; i < m; i++ ){
  
  if( contador == m-1){
     printf("%d", indices[i]);
  }else{
     printf("%d ", indices[i]);
    
  }
  contador++;
}
 printf("\n\n"); 
  
  }
  

  
  return 0;
}