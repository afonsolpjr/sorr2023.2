#include "OS.h"
#include <string.h>
#define QUANTUM 3

/*Display queues situation on terminal*/
void queue_situation(OS kernel,int time,int quantum) 
{
    printf("---------------------------\nTempo corrido: %d\nQuantum: %d\nSituation:\n",time,quantum);
    printc(kernel.new_jobs,"New queue -> ");
    print(kernel.p_alta,"p_alta queue -> ");
    print(kernel.p_baixa,"p_baixa queue -> ");
    printc(kernel.finished,"Finished queue -> ");
    printc(kernel.impressora,"Impressora queue-> ");
    printc(kernel.fita,"Fita queue-> ");
    printc(kernel.disco,"Disco queue-> ");
    if(kernel.executing!=NULL)
    {
        printf("Process running:%d\nRemaining Time:%d\n",kernel.executing->process.PID,
        kernel.executing->process.remaining_time);
    }
    else print(kernel.executing,"Executing-> ");
}

/*Creates a single process*/
proc create_process(int number, char * linha) 
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
            /*Sorted insertions of IO by request time */
            if(new_processo.fila_io == NULL){
                new_processo.fila_io = new_io;
            } 
            else
            {
                temp = new_processo.fila_io;
                if(new_io->instante < temp->instante)
                {
                    new_io->prox_io = temp;
                    new_processo.fila_io = new_io;
                }
                else
                {
                    while(temp->prox_io!= NULL 
                        && 
                        new_io->instante >= temp->prox_io->instante)
                        temp = temp->prox_io;
                    new_io->prox_io = temp->prox_io;
                    temp->prox_io  = new_io;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return new_processo;
    
}

/*Adds all the processes in the file "Processes" in the queue*/
OS preparation(OS kernel,int number_process) 
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

        /* Sorted Insertion on new_jobs queue*/
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
        /* Add_q(&kernel.new_jobs,create_process(i, linha));Creates an process to be scheduled*/
    }
    
    return kernel;
}

void RoundRobin (OS kernel)
{
    int time=0;
    int slice=0;
    while(verifica_filas_vazias(&kernel)==0)
    {
        finish_job(&kernel,time); /*retirar o processo da CPU finalizando-o*/
        verifica_request(&kernel);
        long_term(&kernel,time); /*Admite processos na fila de mais alta prioridade*/
        atualizar_tempo_io(&kernel); /* retirar processos da fila de bloqueio*/
        if(slice == QUANTUM)
        {
            preempt(&kernel);
            slice = 0;
        }
        sobe_prioridade(&kernel,QUANTUM);
        go_processing(&kernel); /* aloca novos processos no processador*/
        if((&kernel)->executing != NULL)
        {
            (&kernel)->executing->process.remaining_time-=1;
        }
        time++;
        slice++;
        queue_situation(kernel,time,slice);
    }
}

int main()
{
    int qtd_proc;
    OS kernel;
    scanf("%d\n", &qtd_proc);
    kernel = start_OS();
    kernel = preparation(kernel,qtd_proc);
    RoundRobin(kernel);

    free(kernel.finished);
    free(kernel.p_alta);
    free(kernel.p_baixa);
    free(kernel.new_jobs);
    free(kernel.disco);
    free(kernel.fita);
    free(kernel.impressora);
    free(kernel.executing);
    return 0;
}