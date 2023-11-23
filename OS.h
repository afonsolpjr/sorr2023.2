#define DISCO 1
#define FITA 2
#define IMPRESSORA 3
#define PRONTO 0
#define RODANDO 1
#define IO 2
#define TERMINADO 3
#define T_DISCO 5
#define T_FITA 10
#define T_IMPRESSORA 15

typedef struct Operational_system
{
    queue *novos_processos;
    queue *p_alta;
    queue *p_baixa;
    queue *finalizados;
    queue *disco;
    queue *fita;
    queue *impressora;
    queue *executando;
} OS;

/*Sistema Operacional*/
OS start_OS(); /*Starts all the values default values*/

/*Gerência de Fila */
void finaliza_processo(OS *kernel, int time);/*Finaliza o processo sendo executado*/
void longo_termo(OS *kernel, int time); /*Admite um processo na fila de prontos*/
int processar(OS *kernel); /*Transfere um programa pro processador*/
int verifica_filas_vazias(OS *kernel); /*Verifica se todas as filas estão vazias*/
void preempt(OS *kernel); /*Retira o programa do processador e coloca na fila de baixa prioridade*/
void sobe_prioridade(OS *kernel, int quantum); /*Se o processo estiver a mais de 5*QUANTUM esperando na fila de baixa prioridade, sobe pra de alta*/

/*Gerência de IO*/
void pedido_IO(OS *kernel,int tipo); /*Trata o pedido de IO do processo*/
void atualizar_tempo_io(OS *kernel); /*Atualiza o tempo de IO dos processos que estão nas filas 
e se terminar manda pra fila correta*/
void verifica_pedido(OS *kernel); /*Verifica se o processo pediu IO*/