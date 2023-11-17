#include <stdio.h>
#include <stdlib.h>

/*Structure of an process*/
typedef struct Process 
{
    int tempo_admissao;
    int PID;  
    int tempo_servico;
    int tempo_restante;
    int tempo_finalizacao;
    int estado;
    int tempo_espera; /*Tempo na fila de baixa prioridade, incrementado a cada unidade de tempo, sobe a cada 10*/
    int tempo_restante_io;
    struct IO * fila_io;
}proc;

typedef struct IO
{
    int tipo;
    int instante;
    struct IO *prox_io;
} io;

/*Queue data structure*/
typedef struct Queue 
{
    proc process;
    struct Queue* next;
}queue;

queue *cria_fila(proc process); /*Cria uma nova fila*/
void Add_q(queue **nova,proc process); /*Adiciona um processo à uma fila, e cria-a se não existir uma*/
void imprime(queue *imprimir,char *frase); /*Imprime uma fila*/
void imprime_condicional(queue *imprimir,char *frase);
proc pop(queue**first); /*Pops a process out of an queue*/
io popIO(io **sai);