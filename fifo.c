#include "OS.h"
void queue_situation(OS kernel) /*Display queues situation on terminal*/
{
    print(kernel.new_jobs,"New queue -> ");
    print(kernel.ready,"Ready queue -> ");
    print(kernel.finished,"Finished queue -> ");
    printf("Process running:%d\nRemaining Time:%d\n",kernel.executing.number,
    kernel.executing.remaining_time);
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
        kernel.executing.remaining_time-=1;
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
    free(kernel.ready);
    return 0;
}