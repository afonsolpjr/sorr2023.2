#include <stdio.h>
#include <stdlib.h>

/*
state 0 = not running
state 1 = running
state 2 = blocked
*/
typedef struct Process /*Structure of an process*/
{
    int admission_time;
    int number;
    int service_time;
    int remaining_time;
    int finish_time;
    int state;
}proc;

typedef struct Queue /*Queue data structure*/
{
    proc process;
    struct Queue* next;
}queue;

queue *new_q(proc process) /*Creates a new queue*/
{
    queue *newer;
    if((newer = (queue *) malloc(sizeof(queue)))==NULL)
    {
        puts("No more space in the queue");
        exit(1);
    }
    newer -> process = process;
    newer->next=NULL;
    return newer;
}
void Add_q(queue **first,proc process) /*Adds a new process to an queue, or creates an queue if there isn't one*/
{
    if(*first==NULL)
    {
        *first = new_q(process);
    }
    
    else
    {
        queue *check = *first;
        queue **save = first;
        while((*save)->next!= NULL)
        {
            (*save) = (*save)->next;
        }
        (*save)->next=new_q(process);
        *first = check;
    }
}
void print(queue *waiting,char *frase) /*Prints an queue from beginning to end*/
{
    if(waiting !=NULL)
    {
        printf("%s",frase);
        while(waiting!= NULL)
        {
            printf("%d ",waiting->process.number);
            waiting=waiting->next;
        }
    }
    else
    {
        printf("%s NULL",frase);
    }
        puts("");
}
proc pop(queue**first) /*Pops a process out of an queue*/
{
    proc removido;
    removido = (*first)->process;
    (*first) = (*first)->next;
    return removido;
}