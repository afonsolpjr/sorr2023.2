#include "OS.h"

OS start_OS() /*Starts all the values default values*/
{
    OS kernel;
    kernel.finished= NULL;
    kernel.p_alta=NULL;
    kernel.p_baixa=NULL;
    kernel.new_jobs = NULL;
    kernel.blocked = NULL;
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
        if(kernel->executing->process.remaining_time == 0 && kernel->executing->process.state==1)
        {
            kernel->executing->process.finish_time=time;   
            Add_q(&(kernel->finished),(kernel->executing->process));
            kernel->executing=NULL;
        }
    }
}

void long_term(OS *kernel, int time) /*Changes a process from new state to ready state*/
{

    if(kernel->new_jobs!=NULL)
    {
        Add_q(&kernel->p_alta,pop(&kernel->new_jobs));
    }
}

void go_processing(OS *kernel) /*Changes a process from ready state to running state*/
{
    if(kernel->p_alta!=NULL && kernel->executing == NULL)
    {
        Add_q(&kernel->executing,pop(&kernel->p_alta));
        kernel->executing->process.state=1;
    }
    else if(kernel -> p_baixa!=NULL && kernel -> executing == NULL)
    {
        Add_q(&kernel->executing,pop(&kernel->p_baixa));
        kernel->executing->process.state=1;
    }
    
}

void IO_request(OS *kernel,int tipo)
{
    kernel->executing->process.state = 3;
    switch(tipo)
    {
        case(DISCO):
        
            Add_q(&kernel->disco,kernel->executing->process);
            break;
        
        case(FITA) :
        
            Add_q(&kernel->fita,kernel->executing->process);
            break;
        
        case(IMPRESSORA) :
        
            Add_q(&kernel->impressora,kernel->executing->process);
            break;
        
    }
    kernel->executing = NULL;
}

void atualizar_tempo_io(OS *kernel) {
    if(kernel->impressora!=NULL){
        kernel->impressora->process.tempo_restante_io--;
        if(kernel->impressora->process.tempo_restante_io == 0){
            Add_q(&kernel->p_alta, pop(&kernel->impressora));
        }
    }

    if(kernel->disco!=NULL){
        kernel->disco->process.tempo_restante_io--;
        if(kernel->disco->process.tempo_restante_io == 0){
            Add_q(&kernel->p_baixa, pop(&kernel->disco));
        }
    }

    if(kernel->fita!=NULL){
        kernel->fita->process.tempo_restante_io--;
        if(kernel->fita->process.tempo_restante_io == 0){
            Add_q(&kernel->p_alta, pop(&kernel->fita));
        }
    }
}

int verifica_filas_vazias(OS *kernel) {
    if(kernel->p_alta == NULL && kernel->p_baixa == NULL && kernel->new_jobs == NULL
    && kernel->blocked == NULL && kernel->disco == NULL && kernel->fita == NULL &&
    kernel->impressora == NULL && kernel->executing == NULL)
        return 1;
    else
        return 0;
}

void preempt(OS *kernel)
{

}