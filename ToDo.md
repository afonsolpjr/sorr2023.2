A fazer:
 - [] Criar filas
    - [X] Alta prioridade
    - [X] Baixa prioridade
    - [X] I/O Disco
    - [X] IO Fita
    - [X] IO Impressora
    - [X] Definir na estrutura do "OS" as novas filas criadas
    - [X] Definir nova inicialização da estrutura do "OS"
    - [] Criar função pra checar se todas filas são nulas (terminação do programa)

 - [X] Renomear process.number pra pid
 - [X] Ver redundância do trade_queue e add_q
 - [] Criar leitor de entradas (no scheduling.h)
 


 
Enquanto todas filas não são nulas:

    Pra cada unidade de tempo:

    - Se tiver processo executando:
        - [] Ver se o processo sendo executado terminou 
            Caso sim:
            - [] Retirar o processo da CPU, finalizando-o
        


    - Gerenciando outras filas:
        - [] Ver se tem algum algum processo a ser admitido na fila de prontos 
        

        - [] Verificar se algum processo sairá das 3 filas de I/O
            - [] Mandar pras filas corretas de acordo com tipo de io
            

        - [] Ve se o slice terminou (slice==QUANTUM)
            Caso sim:
            - [] Retirar o processo
            - [] Recomeçar o slice
    
     - Caso não tenha processo na CPU:
        - [] Admitir processo na CPU (botar na fila de execucao)
        - Checar se filas estão nulas pra terminar 

        
    - [] Diminui o remaining time do processo sendo executado
    - [] Incrementar o timer



    

MACROS:
    - quantum
    - status
    - tempo de io

Duvidas :
 - Prioridade do processo muda? Como vai funcionar? Sim, dinâmico

 Premissas
    - Processos sem prioridade inerente (todos chegam com a mesma propriedade)
    - Processos esperando há mais de 10 unidades na fila de baixa prioridade sobem pra fila de alta prioridade