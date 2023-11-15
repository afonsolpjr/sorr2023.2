#include "OS.h"
#define QUANTUM 4

void RoundRobin (OS *kernel,int proc_n)
{
    int time=0;
    int slice=0;
    while(verifica_filas_vazias(kernel))
    {
        finish_job(kernel,time); /*retirar o processo da CPU finalizando-o*/
        long_term(kernel,time); /*Admite processos na fila de mais alta prioridade*/
        verifica_filas_vazias(kernel); /*Faz o gerenciamento de IO*/
        if(slice == QUANTUM)
        {
            preempt(kernel);
            slice = 0;
        }
        go_processing(kernel);
        if(kernel->executing == NULL)
        {
            kernel->executing->process.remaining_time-=1;
        }
        time++;

    }
}
/* Leitor de entradas */
proc create_process(int number) /*Creates a single process*/
{
    proc new_process;
    scanf("%d",&new_process.service_time);
    new_process.PID=number;
    new_process.remaining_time=new_process.service_time;
    return new_process;
}

int main()
{

    return 0;
}

