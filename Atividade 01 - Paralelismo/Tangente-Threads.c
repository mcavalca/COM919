/*
    Marcelo Cavalca Filho
    33161
    Atividade 1
    Exercicio 2
    Calculo do seno, cosseno, tangente
    atraves de Threads

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h> // para uso de thread

// Estrutura para armazenar os dados principais
struct valores{
    long double x;
    int n;
    long double seno;
    long double cosseno;
};


// Calculo de fatorial
// OBS:
// Calcular antes e armazenar em um vetor
// pode diminuir o tempo de execucao
// para precisoes de valor elevado
long double fat(int n){
    double fatorial = 1;
    for(int i=2; i<=n; i++){
        fatorial *= i;
    }
    return fatorial;
}


// Funcao do thread para calcular o seno
long double calcSen(void * d){

    // Recebe o ponteiro struct de entrada
    struct valores *dados = d;

    for(int i=0; i<dados->n; i++){
        dados->seno += ((pow(-1, i))/(fat(2*i+1)))*pow(dados->x, 2*i+1);
    }
    pthread_exit(0);
}

// Funcao do thread para calcular o cosseno
long double calcCos(void * d){

    // Recebe o ponteiro struct de entrada
    struct valores *dados = d;

    for(int i=0; i<dados->n; i++){
        dados->cosseno += ((pow(-1, i))/(fat(2*i)))*pow(dados->x, 2*i);
    }
    pthread_exit(0);
}

int main(){
    int n;
    long double x, tangente = 0;
    pthread_t thread[2]; // Utilizara 2 threads (2 funcoes simultaneamente)

    // Entrada dos valores
    printf("Entre com o valor de x (radianos)\n> ");
    scanf("%Lf", &x);
    printf("Entre com o valor de n (precisao)\n> ");
    scanf("%d", &n);

    // Inicializacao das threads
    struct valores *dados = (struct valores *) malloc(sizeof(struct valores));

    // Armazenara os dados de entrada na estrutura pre-definida
    dados->x = x;
    dados->n = n;
    dados->seno = 0;
    dados->cosseno = 0;

    // Cria os threads com os parametros
    // Thread[0,1], pois sao 2 funcoes
    // Nulo
    // Funcao atribuida (calcular seno e calcular cosseno)
    // Dados de entrada e saida
    pthread_create(&thread[0], NULL, calcSen, dados);
    pthread_create(&thread[1], NULL, calcCos, dados);

    // Espera o termino dos threads
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    // Impressao dos valores e calculo da tangente
    printf("\nSen(%Lf) = %Lf\n", x, dados->seno);
    printf("\nCos(%Lf) = %Lf\n", x, dados->cosseno);
    tangente = dados->seno/dados->cosseno;
    printf("\nTan(%Lf) = %Lf\n", x, tangente);

    // Finaliza
    return 0;
}
