#include "OS.h"
#include <string.h>
#define QUANTUM 2

/*Display queues situation on terminal*/
void queue_situation(OS kernel,int time,int quantum) 
{
    printf("---------------------------\nTempo corrido: %d\nFatia: %d\nSituacao:\n",time,quantum);
    imprime_condicional(kernel.novos_processos,"Processos Novos -> ");
    imprime(kernel.p_alta,"Prioridade Alta -> ");
    imprime(kernel.p_baixa,"Prioridade Baixa -> ");
    imprime_condicional(kernel.finalizados,"Finalizados -> ");
    imprime_condicional(kernel.impressora,"Fila Impressora-> ");
    imprime_condicional(kernel.fita,"Fila Fita-> ");
    imprime_condicional(kernel.disco,"Fila Disco-> ");
    if(kernel.executando!=NULL)
    {
        printf("Processo Executando ->%d\nTempo de serviço restante:%d\n",kernel.executando->process.PID,
        kernel.executando->process.tempo_restante);
    }
    else imprime(kernel.executando,"Processador-> ");
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

        /* Sorted Insertion on novos_processos queue*/
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
        /* Add_q(&kernel.novos_processos,create_process(i, linha));Creates an process to be scheduled*/
    }
    
    return kernel;
}

void RoundRobin (OS kernel)
{
    int time=0;
    int slice=0;
    while(verifica_filas_vazias(&kernel)==0)
    {
        finaliza_processo(&kernel,time); /*retirar o processo da CPU finalizando-o*/
        verifica_pedido(&kernel);
        longo_termo(&kernel,time); /*Admite processos na fila de mais alta prioridade*/
        atualizar_tempo_io(&kernel); /* retirar processos da fila de bloqueio*/
        if(slice == QUANTUM)
        {
            preempt(&kernel);
            slice = 0;
        }
        sobe_prioridade(&kernel,QUANTUM);
        if(processar(&kernel)== 1) /* aloca novos processos no processador*/
        {
            slice = 0; /*zera o slice*/
        }
        if((&kernel)->executando != NULL)
        {
            (&kernel)->executando->process.tempo_restante-=1;
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

    free(kernel.finalizados);
    free(kernel.p_alta);
    free(kernel.p_baixa);
    free(kernel.novos_processos);
    free(kernel.disco);
    free(kernel.fita);
    free(kernel.impressora);
    free(kernel.executando);
    return 0;
}