#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265;

struct coordenada {int x; int y; int posicao}; // estrutura para armazenar as coordenadas X, Y e armazena também a posicão do fecho convexo

int* closestPair(int *vet, int tam); // exec 1
int* elementUniqueness(int *vet, int *tam); // exec 2
int frequencyDistribution(int *vet, int tam); // exec 3
struct coordenada* convexHull(int *tamanho); //int *tam); // exec 4

void ordenaVetor(int *vet, int esquerdo, int direito); // ordena o vetor de numeros inteiros
void ordenaVetorCoordenada(struct coordenada *vet, int esquerdo, int direito); // ordena o vetor de coordendas de acordo com o X
double angulo(struct coordenada *vetCoord, int p_ant,int p_atual,int p_prox);  // calculo o angulo entre tres pontos, tendo o p_atul como referencia

int main(int argc, char *argv[])
{
  int opcao = 0; 
  
  // Opções do programa
  // 1 = closestPair
  // 2 = elementUniqueness
  // 3 = frequencyDistribution
  // 4 = convexHull
  
  int tam, i;
  int * vet;
                 
  printf("Escolha uma opcao \n");
  printf("1 = Closest Pair \n");
  printf("2 = Element Uniqueness \n");
  printf("3 = Frequency Distribution \n");
  printf("4 = Convex Hull \n");
  scanf("%d", &opcao);
  
  if(opcao < 1 || opcao > 4){ // Opções não disponível
      printf("Escolha uma opcao disponivel \n"); 
  } else if(opcao >= 1 && opcao <= 3 ){ // Opções que utilizam apenas o vetor de inteiros
            if( opcao == 1 ){
                 printf("Voce escolheu Closest Pair\n");
            } else if( opcao == 2 ){
                 printf("Voce escolheu Element Uniqueness\n");
            } else if( opcao == 3 ){
                printf("Voce escolheu Frequency Distribution\n");
            } 
            
            printf("Forneca o tamanho do vetor ");
            scanf("%d", &tam);
            vet = (int*)malloc(tam*sizeof(int));
            int * par, * unico, maiorFrequencia;
  
            for (i=0;i<tam;i++){ // Pega todos os valores para ser adicionado no vetor
                printf("Forneca o valor da %d posicao ", i+1);
                scanf("%d", &vet[i]);
            }
  
            ordenaVetor(vet, 0, tam-1); // Ordena o vetor
       
            if( opcao == 1 ){
                par = closestPair(vet, tam);  // exec 1
                 printf("\n");
                 for (i=0;i<2;i++){
                    printf("%d  ",par[i]);
                 }
            } else if( opcao == 2 ){
                 unico = elementUniqueness(vet, &tam); // exec 2
                 printf("\n");
                 for (i=0;i<tam;i++){
                    printf("%d  ",unico[i]);
                 } 
            } else if( opcao == 3 ){
                printf("\n");
                maiorFrequencia = frequencyDistribution(vet, tam); //exec 3 
                printf("%d",maiorFrequencia);
            } 
            
            free(vet);
     } else if( opcao == 4 ){ //Opção que utiliza o vetor de coordenadas
         printf("Voce escolheu Convex Hull\n");
         struct coordenada * fecho;
         fecho = convexHull(&tam); // Exec 4 
         
         printf("Os pontos do fecho convexo sao: \n");
         for(i = 0; i < tam; i++){         
               printf("(%d/%d)", fecho[i].x, fecho[i].y);
         }      
         
         free (fecho);
     }
       
  
  system("PAUSE");	
  return 0;
}




// Encontra uma dupla de numeros que tem a menor diferenca em todos os termos dado pelo vetor
int * closestPair(int vet[], int tam){ // exec 1
     int i, dif;
     int * par = (int*) malloc(2 * sizeof(int)); // vetor que sera retornado com os dois valos que tem a menor diferenca
     if(tam > 1){
       dif = abs(vet[1] - vet[0]); // pega o modulo da diferneca entre termos.
       par[0] = vet[0];
       par[1] = vet[1];
       for(i=1;i<tam-1;i++){ // pega a diferenca e a posicao do par que tiver a menor diferenca entre todos os valores fornecidos.
          if(abs(vet[i+1]-vet[i]) < dif){
            dif = abs(vet[i+1]-vet[i]); 
            par[0] = vet[i];
            par[1] = vet[i+1];
          }            
       }
     } else { 
        par[0] = vet[0];
        par[1] = '0';
     }
     
     return par;
}

// Identifica os termos que apareceram apenas 1 vez
int* elementUniqueness(int *vet, int *tam){ // exec 2
     int i, j, aux = 0, tamanho = (*tam);
     
     for(i=0;i<tamanho;i++){ // verifica quantas vezes os terno se repetem 
         if(vet[i] == vet [i+1]){
             aux++;            
         } else if(vet[i-1] == vet [i] && vet[i] != vet [i+1]) {
             aux++;
         }       
     }
     (*tam) = tamanho - aux;
     int * unico = (int *) malloc ((*tam)*sizeof(int)); // cria um vetor apenas para os termos que aparecem uma vez
     for(i = 0, j = 0; i < tamanho ; i++){ 
         if(vet[i] == vet [i+1]){
             i++;            
         } else if(vet[i-1] == vet [i] && vet[i] != vet [i+1]) {
         } else {
             unico[j] = vet[i];
             j++;
         }
     }
     return unico;
}

// Encontra o numero que mais repetiu dentro de um vetor dado
int frequencyDistribution(int *vet, int tam){ // exec 3
    int i, j, maior, posicao;
    int * asd = (int *) calloc(tam, sizeof(int)); // inicializa o vetor de tamanho tam com todos os valores == 0

    
    for(i = 0 , j = 1; i < tam ; j++){
          if(vet[i] == vet[j]){
            asd[i]++; // incrementa em um vetor auxiliar o numero de vezes que o termo repete, no caso as posicoes sao respectivas ao vetor vet.
          } else {
            i = j; // pula as posicoes que ja foram contadas e acrescentadas no posicao i
          }     
    }
    maior = asd[0]; 
    posicao  = 0;
    for(i = 1 ; i < tam ; i++){
          if(asd[i] > maior){
                posicao = i; // pega a posicao onde tem o maior numero de repeticoes
          }      
    }
    return vet[posicao];
}

struct coordenada* convexHull(int * tamanho){//int* tamanho) {
         int tam, i;
         printf("Forneca o numero de pontos desejado");
         scanf("%d", &tam);
         struct coordenada *vetCoord = (struct coordenada*)calloc(tam,sizeof(struct coordenada));
         
         for (i=0;i<tam;i++){ // Pega todos os valores das coordendas X e Y para ser adicionado no vetor de Coordenadas
                printf("Forneca o valor da coordenada X da %d posicao ", i+1);
                scanf("%d", &vetCoord[i].x);
                printf("Forneca o valor da coordenada Y da %d posicao ", i+1);
                scanf("%d", &vetCoord[i].y);
                vetCoord[i].posicao = -1;
         }
         
         ordenaVetorCoordenada(vetCoord, 0, tam-1);
         
         for(i = 0;i < tam ;i++){
                 printf("x = %d y = %d \n", vetCoord[i].x, vetCoord[i].y);  
         }
         
         i=0;
         int p_ant = -1, p_atual = 0 , p_prox = 1, p = 1, fim = 0; // 0-false -- 1-verdade
         double maiorAngulo = 0;
         
         vetCoord[p_atual].posicao = 0;

         while(fim != 1){
             for(; p_prox < tam ; p_prox++ ){
                printf("p_prox %d \n", p_prox);  
                if(vetCoord[p_prox].posicao == -1){   
                   double anguloAux = angulo(vetCoord, p_ant, p_atual, p_prox);
                   printf("angulo x %lf \n", anguloAux);  
                   if(anguloAux > maiorAngulo){
                         maiorAngulo = anguloAux;
                         p = p_prox;                 
                         printf("p %d \n", p);
                   }
                }                              
             }
             
             i++;
             vetCoord[p].posicao = i;
             p_ant = p_atual;
             p_atual = p;
             p_prox = p_atual+1; 
             if(p_prox == tam){
                       fim = 1;
             }       
             maiorAngulo = 0; 
         }
         printf("i %d \n", i);
         
         (*tamanho) = i+1;
         struct coordenada *fecho = (struct coordenada*)calloc(i,sizeof(struct coordenada));
         for(i=0 ; i<tam ; i++){
                 if(vetCoord[i].posicao != -1){
                          fecho[vetCoord[i].posicao] = vetCoord[i];     
                          printf("posicao %d \n", vetCoord[i].posicao);
                          printf("fecho x %d \n", fecho[vetCoord[i].posicao].x);
                          printf("fecho x %d \n", fecho[vetCoord[i].posicao].y);   
                          system("PAUSE");      
                 }  
         }
         
 return fecho;
}

void ordenaVetor(int *vet, int esquerda, int direita) { 
    int i, j, x, y;
     
    i = esquerda;
    j = direita;
    x = vet[(esquerda + direita) / 2];
     
    while(i <= j) {
        while(vet[i] < x && i < direita) {
            i++;
        }
        while(vet[j] > x && j > esquerda) {
            j--;
        }
        if(i <= j) {
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > esquerda) {
        ordenaVetor(vet, esquerda, j);
    }
    if(i < direita) {
        ordenaVetor(vet, i, direita);
    }

}

void ordenaVetorCoordenada(struct coordenada *vetCoord, int esquerda, int direita) { // ordena o vetor de struct coordenada em relacao ao X
    int i, j;
    struct coordenada a, b;
     
    i = esquerda;
    j = direita;
    a = vetCoord[(esquerda + direita) / 2];
     
    while(i <= j) {
        while(vetCoord[i].x < a.x && i < direita) {
            i++;
        }
        while(vetCoord[j].x > a.x && j > esquerda) {
            j--;
        }
        if(i <= j) {
            b = vetCoord[i];
            vetCoord[i] = vetCoord[j];
            vetCoord[j] = b;
            i++;
            j--;
        }
    }
     
    if(j > esquerda) {
        ordenaVetorCoordenada(vetCoord, esquerda, j);
    }
    if(i < direita) {
        ordenaVetorCoordenada(vetCoord, i, direita);
    }
}

double angulo(struct coordenada *vetCoord, int p_ant,int p_atual,int p_prox){
      // printf("ant %d atual %d prox %d \n", p_ant, p_atual, p_prox);
      int produto = 0;
      double modulo;
      double ang;
      if (p_ant == -1){
         produto = (-1)*(vetCoord[p_prox].y - vetCoord[p_atual].y);
         modulo = pow(pow((vetCoord[p_prox].x - vetCoord[p_atual].x), 2) + pow((vetCoord[p_prox].y - vetCoord[p_atual].y), 2) ,0.5);   
         ang = acos(produto/modulo)*180/PI; // *180/PI converte o angulo de radianos para grau
      } else {
         produto = (vetCoord[p_ant].x - vetCoord[p_atual].x)*(vetCoord[p_prox].x - vetCoord[p_atual].x) + (vetCoord[p_ant].y - vetCoord[p_atual].y)*(vetCoord[p_prox].y - vetCoord[p_atual].y);
         modulo = pow(pow((vetCoord[p_ant].x - vetCoord[p_atual].x), 2) + pow((vetCoord[p_ant].y - vetCoord[p_atual].y), 2) , 0.5) * pow(pow((vetCoord[p_prox].x - vetCoord[p_atual].x), 2) + pow((vetCoord[p_prox].y - vetCoord[p_atual].y), 2) , 0.5);   
         ang = acos(produto/modulo)*180/PI; // *180/PI converte o angulo de radianos para grau
      }      
      return ang;
}
