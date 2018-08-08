/*
    Marcelo Cavalca Filho
    33161
    Atividade 1
    Exercicio 1
    Calculo do seno, cosseno, tangente
    atraves de Processos

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h> // para pow()

long double fat(int n){
    double fatorial = 1;
    for(int i=2; i<=n; i++){
        fatorial *= i;
    }
    return fatorial;
}

long double calcSen(long double x, int n){
    long double seno = 0;
    for(int i=0; i<n; i++){
        seno += ((pow(-1, i))/(fat(2*i+1)))*pow(x, 2*i+1);
    }
    return seno;
}

long double calcCos(long double x, int n){
    long double cosseno = 0;
    for(int i=0; i<n; i++){
        cosseno += ((pow(-1, i))/(fat(2*i)))*pow(x, 2*i);
    }
    return cosseno;
}

int main(){
    // Inicializacao de variaveis
    int n;
    long double seno, cosseno, x, tangente = 0;
    pid_t pid;
    int fd[2]; // Pipe

    printf("Entre com o valor de x (radianos)\n> ");
    scanf("%Lf", &x);
    printf("Entre com o valor de n (precisao)\n> ");
    scanf("%d", &n);

    // Se houver erro com a criacao do pipe
    if(pipe(fd) < 0){
        perror("pipe");
        return -1;
    }

    // Se nao for possivel criar o processo
    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    // Processo filho
    // Calcula o cosseno
    if(pid == 0) {
        cosseno = calcCos(x, n);
        printf("\nCos(%Lf) = %Lf\n", x, cosseno);
        // Apos o calculo, envia ao processo pai, atraves do pipe
        // o valor do cosseno
        close(fd[0]);
        write(fd[1], &cosseno, sizeof(cosseno));
        exit(0);

    // Processo pai
    // Calcula o seno
    } else {
        seno = calcSen(x, n);
        printf("\nSen(%Lf) = %Lf\n", x, seno);
        // O processo pai deve receber o valor do cosseno gerado pelo filho
        // para que possa calcular a tangente
        close(fd[1]);
        read(fd[0], &cosseno, sizeof(cosseno));
    }

    // Espera ate que o filho tenha terminado
    // para o...
    wait(&pid);
    // Calculo da tangente
    tangente = seno/cosseno;
    printf("\nTan(%Lf) = %Lf\n", x, seno/cosseno);
    return 0;
}
