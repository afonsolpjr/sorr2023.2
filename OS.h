#include "scheduling.h"
typedef struct Operational_system
{
    queue *new_jobs;
    queue *ready;
    queue *finished;
    queue *blocked;
    queue *executing;
} OS;

OS start_OS() /*Starts all the values default values*/
{
    OS kernel;
    kernel.finished= NULL;
    kernel.new_jobs = NULL;
    kernel.ready = NULL;
    kernel.blocked = NULL;
    kernel.executing = NULL;
    return kernel;
}


void finish_job(OS *kernel, int time) /*Changes a job from processor to finished queue*/
{
    if(kernel->executing!=NULL)
    {
        if(kernel->executing->process.remaining_time == 0 && kernel->executing->process.state==1)
        {
            kernel->executing->process.finish_time=time;   
            Add_q(&(kernel->finished),(kernel->executing->process));
            kernel->executing=NULL;
        }
    }
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
    if(kernel->ready!=NULL && kernel->executing == NULL)
    {
        Add_q(&kernel->executing,pop(&kernel->ready));
        kernel->executing->process.state=1;
    }
}

void IO_request(OS *kernel,int *time)
{
    Add_q(&kernel->blocked,kernel->executing->process);
    kernel->executing = NULL;
}