#include "OS.c"
#include <string.h>
#include <stdlib.h>
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

proc create_process(int number, char * linha) /*Creates a single process*/
{   
    int i;
    char *token;
    int num_admissao, num_servico, instante, tipo;
    io * new_io;
    proc new_processo;
    io * temp;

    new_processo.PID=number;
    token = strtok(linha, " ");
    num_admissao = atoi(token);
    new_processo.admission_time = num_admissao;
    token = strtok(NULL, " ");
    num_servico = atoi(token);
    new_processo.service_time = num_servico;
    new_processo.remaining_time=new_processo.service_time;
    token = strtok(NULL, " ");
    for(i=0; token != NULL; i++){
        if(i % 2 == 0){
            tipo = atoi(token);
        } else{
            instante = atoi(token);
            new_io = (io*) malloc(sizeof(io));
            new_io->tipo = tipo;
            new_io->instante = instante;
            new_io->prox_io = NULL;
            if(new_processo.fila_io == NULL){
                new_processo.fila_io = new_io;
            } else{
                temp = new_processo.fila_io;
                while(temp->prox_io != NULL){
                    temp=temp->prox_io;
                }
                temp->prox_io = new_io;
            }
        }
        token = strtok(NULL, " ");
    }

    /*printf("PROCESSO CRIADO COM SUCESSO\n");
    printf("--------------------------------\n");
    printf("admissão: %d\ntempo de serviço: %d\npid: %d\nremaining time: %d", new_processo.admission_time, new_processo.service_time, new_processo.PID, new_processo.remaining_time);
    printf("\nlista io:\n");
    temp = new_processo.fila_io;
    while(temp != NULL){
        printf("tipo: %d instante: %d\n", temp->tipo, temp->instante);
        temp=temp->prox_io;
    }
    printf("--------------------------------\n\n");*/
    return new_processo;
    
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
    char linha[100];
    proc new_proc;
    queue *to_add;
    queue *check;
    for (i=0;i<number_process;i++)
    {
        fgets(linha, 100, stdin);
        new_proc = create_process(i,linha);

        /* Insertion Sort on new_jobs queue*/
        to_add = new_q(new_proc);
        if(kernel.new_jobs==NULL)
        {
            kernel.new_jobs = to_add;
        }
        else
        {
            if(new_proc.admission_time < kernel.new_jobs->process.admission_time)
            {
                to_add->next = kernel.new_jobs;
                kernel.new_jobs = to_add;
            }
            else
            {
                check = kernel.new_jobs;
                while(check->next!=NULL 
                && new_proc.admission_time>=check->next->process.admission_time)
                {
                    check = check->next;
                }
                to_add->next= check->next;
                check->next = to_add;
            }
            
        }
        // Add_q(&kernel.new_jobs,create_process(i, linha)); /*Creates an process to be scheduled*/
    }


    
    return kernel;
}
int main(int argc , char *argv[])
{
    int qtd_proc;
    OS kernel;
    scanf("%d\n", &qtd_proc);
    kernel = start_OS();
    kernel = preparation(kernel,qtd_proc);
    fifo(kernel,qtd_proc);
    free(kernel.new_jobs);
    free(kernel.finished);
    free(kernel.p_alta);
    free(kernel.blocked);
    free(kernel.executing);
    return 0;
}