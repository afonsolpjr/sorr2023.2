#include "OS.c"
#include <string.h>
#include <stdlib.h>
void queue_situation(OS kernel) /*Display queues situation on terminal*/
{
    imprime(kernel.novos_processos,"New queue -> ");
    imprime(kernel.p_alta,"p_alta queue -> ");
    imprime(kernel.p_baixa,"p_baixa queue -> ");
    imprime(kernel.finalizados,"finalizados queue -> ");
    imprime(kernel.impressora,"Impressora queue-> ");
    imprime(kernel.fita,"Fita queue-> ");
    imprime(kernel.disco,"Disco queue-> ");
    if(kernel.executando!=NULL)
    {
        printf("Process running:%d\nRemaining Time:%d\n",kernel.executando->process.PID,
        kernel.executando->process.tempo_restante);
    }
    else imprime(kernel.executando,"executando-> ");
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
    new_processo.tempo_admissao = num_admissao;
    token = strtok(NULL, " ");
    num_servico = atoi(token);
    new_processo.tempo_servico = num_servico;
    new_processo.tempo_restante=new_processo.tempo_servico;
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
    printf("admissão: %d\ntempo de serviço: %d\npid: %d\nremaining time: %d", new_processo.tempo_admissao, new_processo.tempo_servico, new_processo.PID, new_processo.tempo_restante);
    printf("\nlista io:\n");
    temp = new_processo.fila_io;
    while(temp != NULL){
        printf("tipo: %d instante: %d\n", temp->tipo, temp->instante);
        temp=temp->prox_io;
    }
    printf("--------------------------------\n\n");*/
    return new_processo;
    
}

int pc(OS kernel) /*Counts how many processes have finalizados*/
{
    int contador=0;
    while(kernel.finalizados!=NULL)
    {
        contador++;
        kernel.finalizados = kernel.finalizados->next;
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
        
        finaliza_processo(&kernel,time);
        longo_termo(&kernel,time);
        processar(&kernel);
        if(kernel.executando!=NULL)
        {
            kernel.executando->process.tempo_restante-=1;
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

        /* Insertion Sort on novos_processos queue*/
        to_add = cria_fila(new_proc);
        if(kernel.novos_processos==NULL)
        {
            kernel.novos_processos = to_add;
        }
        else
        {
            if(new_proc.tempo_admissao < kernel.novos_processos->process.tempo_admissao)
            {
                to_add->next = kernel.novos_processos;
                kernel.novos_processos = to_add;
            }
            else
            {
                check = kernel.novos_processos;
                while(check->next!=NULL 
                && new_proc.tempo_admissao>=check->next->process.tempo_admissao)
                {
                    check = check->next;
                }
                to_add->next= check->next;
                check->next = to_add;
            }
            
        }
        // Add_q(&kernel.novos_processos,create_process(i, linha)); /*Creates an process to be scheduled*/
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
    free(kernel.novos_processos);
    free(kernel.finalizados);
    free(kernel.p_alta);
    free(kernel.executando);
    return 0;
}