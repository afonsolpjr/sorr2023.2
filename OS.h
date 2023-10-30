#include "scheduling.h"
typedef struct Operational_system
{
    queue *new_jobs;
    queue *ready;
    queue *finished;
    proc executing;
} OS;

OS start_OS() /*Starts all the values default values*/
{
    OS kernel;
    kernel.finished= NULL;
    kernel.new_jobs = NULL;
    kernel.ready = NULL;
    kernel.executing.state=0;
    return kernel;
}

void long_term(OS *kernel, int time) /*Changes a process from new state to ready state*/
{

    if(kernel->new_jobs!=NULL)
    {
        trade_queue(&kernel->new_jobs,&kernel->ready);
    }
}
void go_processing(OS *kernel) /*Changes a process from ready state to running state*/
{
    if(kernel->ready!=NULL && kernel->executing.state==0)
    {
        kernel->executing = pop(&(kernel->ready));
        kernel->executing.state=1;
    }
}
void finish_job(OS *kernel, int time) /*Changes a job from processor to finished queue*/
{

    if(kernel->executing.remaining_time == 0 && kernel->executing.state==1)
    {
        kernel->executing.finish_time=time;   
        kernel->executing.state=0;
        Add_q(&(kernel->finished),(kernel->executing));
    }
}