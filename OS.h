#include "queues.h"
#define DISCO 1
#define FITA 2
#define IMPRESSORA 3
#define PRONTO 0
#define RODANDO 1
#define IO 2
#define TERMINADO 3
#define T_DISCO 5
#define T_FITA 10
#define T_IMPRESSORA 15

typedef struct Operational_system
{
    queue *new_jobs;
    queue *p_alta;
    queue *p_baixa;
    queue *finished;
    queue *disco;
    queue *fita;
    queue *impressora;
    queue *executing;
} OS;

OS start_OS(); /*Starts all the values default values*/
void finish_job(OS *kernel, int time);/*Changes a job from processor to finished queue*/
void long_term(OS *kernel, int time); /*Changes a process from new state to ready state*/
int go_processing(OS *kernel); /*Changes a process from ready state to running state*/
void IO_request(OS *kernel,int tipo); /*Trata o pedido de IO do processo*/
void atualizar_tempo_io(OS *kernel); /*Atualiza o tempo de IO dos processos que estão nas filas 
e se terminar manda pra fila correta*/
int verifica_filas_vazias(OS *kernel); /*Verifica se todas as filas estão vazias*/
void preempt(OS *kernel); /*Retira o programa do processador e coloca na fila de baixa prioridade*/
void sobe_prioridade(OS *kernel, int quantum); /*Se o processo estiver a mais de 5*QUANTUM esperando na fila de baixa prioridade, sobe pra de alta*/
void verifica_request(OS *kernel); /*Verifica se o processo pediu IO*/