#include "queues.h"
#define QUANTUM 4

/* Leitor de entradas */
proc create_process(int number) /*Creates a single process*/
{
    proc new_process;
    scanf("%d",&new_process.service_time);
    new_process.number=number;
    new_process.remaining_time=new_process.service_time;
    return new_process;
}

int main()
{




    return 0;
}

