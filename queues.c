#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
/*
estado 0 = not running
estado 1 = running
estado 2 = blocked
*/

/*Creates a new queue*/
queue *cria_fila(proc process) 
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
void Add_q(queue **nova,proc process)
{
    if(*nova==NULL)
    {
        *nova = cria_fila(process);
    }
    
    else
    {
        queue *check = *nova;
        queue **save = nova;
        while((*save)->next!= NULL)
        {
            (*save) = (*save)->next;
        }
        (*save)->next=cria_fila(process);
        *nova = check;
    }
}

/*Prints an queue from beginning to end*/
void imprime(queue *imprimir,char *frase) {
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
void imprime_condicional(queue *imprimir,char *frase)
{
    if(imprimir != NULL)
    {
        imprime(imprimir,frase);
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

io popIO(io **sai)
{
    io removido;
    removido = **sai;
    (*sai) = (*sai)->prox_io;
    return removido;
}