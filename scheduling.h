#include "structures.h"

queue *trade_queue(queue **old,queue**newer) /*changes a process from an old queue to a new one*/
{
    Add_q(newer,pop(old));
}
proc create_process(int number) /*Creates a single process*/
{
    proc new_process;
    scanf("%d",&new_process.service_time);
    new_process.number=number;
    new_process.remaining_time=new_process.service_time;
    return new_process;
}

