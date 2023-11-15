A fazer:

- [] Criar filas

  - [x] Alta prioridade
  - [x] Baixa prioridade
  - [x] I/O Disco
  - [x] IO Fita
  - [x] IO Impressora
  - [x] Definir na estrutura do "OS" as novas filas criadas
  - [x] Definir nova inicialização da estrutura do "OS"
  - [X] Criar função pra checar se todas filas são nulas (terminação do programa)

- [x] Renomear process.number pra pid
- [x] Ver redundância do trade_queue e add_q
- [] Criar leitor de entradas (no scheduling.h)

Enquanto todas filas não são nulas:

    Pra cada unidade de tempo:

    - Se tiver processo executando:
        - [X] Ver se o processo sendo executado terminou
            Caso sim:
            - [X] Retirar o processo da CPU, finalizando-o



    - Gerenciando outras filas:
        - [X] Ver se tem algum algum processo a ser admitido na fila de prontos


        - [] Verificar se algum processo sairá das 3 filas de I/O
            - [] Mandar pras filas corretas de acordo com tipo de io


        - [X] Ve se o slice terminou (slice==QUANTUM)
            Caso sim:
            - [] Retirar o processo
            - [X] Recomeçar o slice

     - Caso não tenha processo na CPU:
        - [X] Admitir processo na CPU (botar na fila de execucao)
        - [X] Checar se filas estão nulas pra terminar


    - [X] Diminui o remaining time do processo sendo executado
    - [X] Incrementar o timer

MACROS: - quantum - status - tempo de io

    - [] Implementar mudança de fila do processo quando ele espera por mais de 10 unidades de tempo
    - [X] Implementar Preempt (Retirar o processo de execução e colocar na baixa prioridade)
        - mano foi só uma linha kkk
    - [X] Implementar diferentes tempos de admissão do processo
    - [] Colocar create_process no aquivo correto
    - [] Checar quais filas estão sendo usadas para poder retirar as que não estão
        - a "blocked" não é utilizada
    - [] Dar free nas que foram alocadas no programa
        - acho que o local propicio pra isso é no finishing_job, ne?
    - [] Definir MACROS de status
Duvidas :

- Prioridade do processo muda? Como vai funcionar? Sim, dinâmico

Premissas - Processos sem prioridade inerente (todos chegam com a mesma prioriedade) 
- Processos esperando há mais de 10 unidades na fila de baixa prioridade sobem pra fila de alta prioridade
