#include "OS.h"

OS start_OS() /*Starts all the values default values*/
{
    OS kernel;
    kernel.finished= NULL;
    kernel.p_alta=NULL;
    kernel.p_baixa=NULL;
    kernel.new_jobs = NULL;
    kernel.disco=NULL;
    kernel.fita=NULL;
    kernel.impressora=NULL;
    kernel.executing = NULL;
    return kernel;
}

void finish_job(OS *kernel, int time) /*Changes a job from processor to finished queue*/
{
    if(kernel->executing!=NULL)
    {
        if(kernel->executing->process.remaining_time == 0 && kernel->executing->process.state==RODANDO)
        {
            kernel->executing->process.finish_time=time;
            kernel->executing->process.state = TERMINADO;   
            Add_q(&(kernel->finished),(kernel->executing->process));
            kernel->executing=NULL;
        }
    }
}

void long_term(OS *kernel, int time) /*Changes a process from new state to ready state*/
{
    if(kernel->new_jobs!=NULL)
    {
        while(kernel->new_jobs->process.admission_time == time)
        {
            kernel->new_jobs->process.state=PRONTO;
            Add_q(&kernel->p_alta,pop(&kernel->new_jobs));
            if(kernel->new_jobs==NULL) break;
        }
    }
}

int go_processing(OS *kernel) /*Changes a process from ready state to running state*/
{
    if(kernel->p_alta!=NULL && kernel->executing == NULL)
    {
        Add_q(&kernel->executing,pop(&kernel->p_alta));
        kernel->executing->process.state=RODANDO;
        return 1;
    }
    else if(kernel -> p_baixa!=NULL && kernel -> executing == NULL)
    {
        Add_q(&kernel->executing,pop(&kernel->p_baixa));
        kernel->executing->process.state=RODANDO;
        return 1;
    }
    return 0;
    
}


void IO_request(OS *kernel,int tipo)
{
    kernel->executing->process.state = TERMINADO;
    switch(tipo)
    {
        case(DISCO):
            kernel->executing->process.tempo_restante_io=T_DISCO;
            Add_q(&kernel->disco,kernel->executing->process);
            popIO(&kernel->disco->process.fila_io);
            break;
        
        case(FITA) :
            kernel->executing->process.tempo_restante_io=T_FITA;
            Add_q(&kernel->fita,kernel->executing->process);
            popIO(&kernel->fita->process.fila_io);
            break;
        
        case(IMPRESSORA) :
            kernel->executing->process.tempo_restante_io=T_IMPRESSORA;
            Add_q(&kernel->impressora,kernel->executing->process);
            popIO(&kernel->impressora->process.fila_io);
            break;
        
    }
    kernel->executing = NULL;
}

void verifica_request(OS *kernel)
{
    int tempo_executando;
    if(kernel->executing!=NULL)
    {
        if(kernel->executing->process.fila_io!=NULL)
        {
            tempo_executando = kernel->executing->process.service_time-kernel->executing->process.remaining_time;
            if(tempo_executando == kernel->executing->process.fila_io->instante)
            {
                IO_request(kernel,kernel->executing->process.fila_io->tipo);
            }
        }
    }
}
void atualizar_tempo_io(OS *kernel) {
    if(kernel->impressora!=NULL){
        kernel->impressora->process.tempo_restante_io--;
        if(kernel->impressora->process.tempo_restante_io == 0){
            kernel->impressora->process.state=PRONTO;
            Add_q(&kernel->p_alta, pop(&kernel->impressora));
        }
    }

    if(kernel->disco!=NULL){
        kernel->disco->process.tempo_restante_io--;
        if(kernel->disco->process.tempo_restante_io == 0){
            kernel->disco->process.state=PRONTO;
            Add_q(&kernel->p_baixa, pop(&kernel->disco));
        }
    }

    if(kernel->fita!=NULL){
        kernel->fita->process.tempo_restante_io--;
        if(kernel->fita->process.tempo_restante_io == 0){
            kernel->fita->process.state=PRONTO;
            Add_q(&kernel->p_alta, pop(&kernel->fita));
        }
    }
}

int verifica_filas_vazias(OS *kernel) {
    if(kernel->p_alta == NULL && kernel->p_baixa == NULL && kernel->new_jobs == NULL
    && kernel->disco == NULL && kernel->fita == NULL &&
    kernel->impressora == NULL && kernel->executing == NULL)
        return 1;
    else
        return 0;
}

void preempt(OS *kernel)
{
    if(kernel ->executing !=NULL)
    {
        kernel->executing->process.state=PRONTO;
        Add_q(&kernel->p_baixa,pop(&kernel->executing));
    }
}

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
            {
                break;
            }
        }
    }
}