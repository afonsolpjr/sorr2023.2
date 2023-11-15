#include "queues.h"
#define DISCO 1
#define FITA 2
#define IMPRESSORA 3
typedef struct Operational_system
{
    queue *new_jobs;
    queue *p_alta;
    queue *p_baixa;
    queue *finished;
    queue *blocked;
    queue *disco;
    queue *fita;
    queue *impressora;
    queue *executing;
} OS;

OS start_OS(); /*Starts all the values default values*/
void finish_job(OS *kernel, int time);/*Changes a job from processor to finished queue*/
void long_term(OS *kernel, int time); /*Changes a process from new state to ready state*/
void go_processing(OS *kernel); /*Changes a process from ready state to running state*/
void IO_request(OS *kernel,int tipo); /*Trata o pedido de IO do processo*/
void atualizar_tempo_io(OS *kernel); /*Atualiza o tempo de IO dos processos que estão nas filas*/
int verifica_filas_vazias(OS *kernel); /*Verifica se todas as filas estão vazias*/