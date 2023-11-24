#include "OS.h"

OS start_OS() /*Starts all the values default values*/
{
    OS kernel;
    kernel.finalizados= NULL;
    kernel.p_alta=NULL;
    kernel.p_baixa=NULL;
    kernel.novos_processos = NULL;
    kernel.disco=NULL;
    kernel.fita=NULL;
    kernel.impressora=NULL;
    kernel.executando = NULL;
    return kernel;
}

int finaliza_processo(OS *kernel, int time) /*Changes a job from processor to finalizados queue*/
{
    if(kernel->executando->process.tempo_restante == 0 && kernel->executando->process.estado==RODANDO)
    {
        kernel->executando->process.tempo_finalizacao=time;
        kernel->executando->process.estado = TERMINADO;   
        Add_q(&(kernel->finalizados),(kernel->executando->process));
        kernel->executando=NULL;
        printf("\nProcesso %d finalizado em %d\n",
        kernel->finalizados->process.PID,time);
        return 1;
    }
    return 0;
}

void longo_termo(OS *kernel, int time) /*Changes a process from new estado to ready estado*/
{
    if(kernel->novos_processos!=NULL)
    {
        while(kernel->novos_processos->process.tempo_admissao == time)
        {
            kernel->novos_processos->process.estado=PRONTO;
            Add_q(&kernel->p_alta,pop(&kernel->novos_processos));
            if(kernel->novos_processos==NULL) break;
        }
    }
}

int processar(OS *kernel) /*Changes a process from ready estado to running estado*/
{
    if(kernel->p_alta!=NULL && kernel->executando == NULL)
    {
        Add_q(&kernel->executando,pop(&kernel->p_alta));
        kernel->executando->process.estado=RODANDO;
        return 1;
    }
    else if(kernel -> p_baixa!=NULL && kernel -> executando == NULL)
    {
        Add_q(&kernel->executando,pop(&kernel->p_baixa));
        kernel->executando->process.estado=RODANDO;
        return 1;
    }
    return 0;
    
}


void pedido_IO(OS *kernel,int tipo)
{
    kernel->executando->process.estado = IO;
    popIO(&kernel->executando->process.fila_io);
    
    switch(tipo)
    {
        case(DISCO):
            kernel->executando->process.tempo_restante_io=T_DISCO;
            Add_q(&kernel->disco,kernel->executando->process);
            break;
        
        case(FITA) :
            kernel->executando->process.tempo_restante_io=T_FITA;
            Add_q(&kernel->fita,kernel->executando->process);
            break;
        
        case(IMPRESSORA) :
            kernel->executando->process.tempo_restante_io=T_IMPRESSORA;
            Add_q(&kernel->impressora,kernel->executando->process);
            break;
        
    }
    kernel->executando = NULL;
}

/* Verifica se o processo ativo vai pedir uma operação de E/S no instante atual */
int verifica_pedido(OS *kernel)
{
    int tempo_executando;
    if(kernel->executando->process.fila_io!=NULL)
    {
        tempo_executando = kernel->executando->process.tempo_servico-kernel->executando->process.tempo_restante;
        if(tempo_executando == kernel->executando->process.fila_io->instante)
        {
            pedido_IO(kernel,kernel->executando->process.fila_io->tipo);
            return 1;
        }
    }
    return 0;
}
/* Retira processos das filas bloqueadas de I/O */

void atualizar_tempo_io(OS *kernel) {
    if(kernel->impressora!=NULL){

        if(kernel->impressora->process.tempo_restante_io == 0){
            kernel->impressora->process.estado=PRONTO;
            Add_q(&kernel->p_alta, pop(&kernel->impressora));
        }
        else 
            kernel->impressora->process.tempo_restante_io--;
    }

    if(kernel->disco!=NULL){
        if(kernel->disco->process.tempo_restante_io == 0){
            kernel->disco->process.estado=PRONTO;
            Add_q(&kernel->p_baixa, pop(&kernel->disco));
        }
        else
            kernel->disco->process.tempo_restante_io--;
    }

    if(kernel->fita!=NULL){
        if(kernel->fita->process.tempo_restante_io == 0){
            kernel->fita->process.estado=PRONTO;
            Add_q(&kernel->p_alta, pop(&kernel->fita));
        }
        else
            kernel->fita->process.tempo_restante_io--;
    }
}

int verifica_filas_vazias(OS *kernel) {
    if(kernel->p_alta == NULL && kernel->p_baixa == NULL && kernel->novos_processos == NULL
    && kernel->disco == NULL && kernel->fita == NULL &&
    kernel->impressora == NULL && kernel->executando == NULL)
        return 1;
    else
        return 0;
}

void preempt(OS *kernel)
{
    if(kernel ->executando !=NULL)
    {
        kernel->executando->process.estado=PRONTO;
        Add_q(&kernel->p_baixa,pop(&kernel->executando));
    }
}
/* Checa tempo de espera de processos na baixa prioridade, e sobe a prioridade*/
/* deles caso estejam lá pelo tempo determinado */
void sobe_prioridade(OS *kernel, int quantum)
{
    if(kernel->p_baixa != NULL)
    {
        while(kernel->p_baixa->next!=NULL)
        {
            if(kernel->p_baixa->process.tempo_espera == quantum*5)
            {
                Add_q(&kernel->p_alta,pop(&kernel->p_baixa));
            }
            else
                break;
        }
    }
}