#include "queues.h"
#define QUANTUM 4

void fifo (OS kernel,int proc_n)
{
    time=0;
    finish_job(&kernel,time);
    long_term(&kernel,time);
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

