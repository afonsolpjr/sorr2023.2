#define DISCO 1
#define FITA 2
#define IMPRESSORA 3
#define PRONTO 0
#define RODANDO 1
#define IO 2
#define TERMINADO 3
#define T_DISCO 2
#define T_FITA 4
#define T_IMPRESSORA 5

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

/*Checa se o processo ativo acabou.
Retorna 1 ele tenha sido finalizado
Retorna 0 caso não.*/
int finaliza_processo(OS *kernel, int time);
/*Admite um processo da fila de admissão na fila de prontos*/
void longo_termo(OS *kernel, int time); 
int processar(OS *kernel); /*Transfere um programa pro processador*/
/*Verifica se todas as filas estão vazias. Retorno: 1 caso filas vazias,
 0 caso ainda haja processos em filas.*/
int verifica_filas_vazias(OS *kernel); 
/*Retira o programa do processador e coloca na fila de baixa prioridade*/
void preempt(OS *kernel); 
/*Se o processo estiver a mais de 5*QUANTUM esperando na fila de baixa prioridade, sobe pra de alta*/
void sobe_prioridade(OS *kernel, int quantum); 
/*Gerência de IO*/
/*Trata o pedido de IO do processo.
Desalocando-o da CPU e alocando-o na fila correta*/
void pedido_IO(OS *kernel,int tipo); 
/*Atualiza o tempo de IO dos processos que estão nas filas 
e, caso terminado a operação, aloca na fila correta*/
void atualizar_tempo_io(OS *kernel); 
/*Verifica se o processo pediu IO 
no instante de tempo atual*/
int verifica_pedido(OS *kernel); 