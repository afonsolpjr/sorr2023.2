#include "OS.h"
void queue_situation(OS kernel) /*Display queues situation on terminal*/
{
    print(kernel.new_jobs,"New queue -> ");
    print(kernel.p_alta,"p_alta queue -> ");
    print(kernel.p_baixa,"p_baixa queue -> ");
    print(kernel.finished,"Finished queue -> ");
    print(kernel.blocked,"Blocked queue-> ");
    if(kernel.executing!=NULL)
    {
        printf("Process running:%d\nRemaining Time:%d\n",kernel.executing->process.PID,
        kernel.executing->process.remaining_time);
    }
    else print(kernel.executing,"Executing-> ");
}

proc create_process(int number) /*Creates a single process*/
{
    proc new_process;
    scanf("%d",&new_process.service_time);
    new_process.PID=number;
    new_process.remaining_time=new_process.service_time;
    return new_process;
}

int pc(OS kernel) /*Counts how many processes have finished*/
{
    int contador=0;
    while(kernel.finished!=NULL)
    {
        contador++;
        kernel.finished = kernel.finished->next;
    }
    return contador;
}
void fifo(OS kernel,int proc_n) /*FCFS scheduling algorithm*/
{
    int counter=0;
    int time=0;
    while(counter!= proc_n)
    {
        time++;
        
        finish_job(&kernel,time);
        long_term(&kernel,time);
        go_processing(&kernel);
        if(kernel.executing!=NULL)
        {
            kernel.executing->process.remaining_time-=1;
        }
        printf("---------------------------\nUnity time: %d\nSituation:\n",time);
        queue_situation(kernel);
        counter = pc(kernel);
    }
}
OS preparation(OS kernel,int number_process) /*Adds all the processes in the file "Processes" in the queue*/
{
    int i;
    for (i=0;i<number_process;i++)
    {
        Add_q(&kernel.new_jobs,create_process(i)); /*Creates an process to be scheduled*/
    }
    return kernel;
}
int main(int argc , char *argv[])
{
    OS kernel;
    kernel = start_OS();
    kernel = preparation(kernel,5);
    fifo(kernel,5);
    free(kernel.new_jobs);
    free(kernel.finished);
    free(kernel.p_alta);
    free(kernel.blocked);
    free(kernel.executing);
    return 0;
}