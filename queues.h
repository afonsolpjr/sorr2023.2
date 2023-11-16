#include <stdio.h>
#include <stdlib.h>

/*Structure of an process*/
typedef struct Process 
{
    int admission_time;
    int PID;  
    int service_time;
    int remaining_time;
    int finish_time;
    int state;
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
queue *new_q(proc process); /*Creates a new queue*/
void Add_q(queue **first,proc process); /*Adds a new process to an queue, or creates an queue if there isn't one*/
void print(queue *waiting,char *frase); /*Prints an queue from beginning to end*/
proc pop(queue**first); /*Pops a process out of an queue*/