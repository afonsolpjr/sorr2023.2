#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
/*
state 0 = not running
state 1 = running
state 2 = blocked
*/

/*Creates a new queue*/
queue *new_q(proc process) 
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

 /*Adds a new process to an queue, or creates an queue if there isn't one*/
void Add_q(queue **first,proc process)
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

/*Prints an queue from beginning to end*/
void print(queue *imprimir,char *frase) {
    if(imprimir !=NULL)
    {
        printf("%s",frase);
        while(imprimir!= NULL)
        {
            printf("%d ",imprimir->process.PID);
            imprimir=imprimir->next;
        }
    }
    else
    {
        printf("%s NULL",frase);
    }
        puts("");
}
void printc(queue *imprimir,char *frase)
{
    if(imprimir != NULL)
    {
        print(imprimir,frase);
    }
}
/*Pops a process out of an queue*/
proc pop(queue**first) 
{
    proc removido;
    removido = (*first)->process;
    (*first) = (*first)->next;
    return removido;
}
