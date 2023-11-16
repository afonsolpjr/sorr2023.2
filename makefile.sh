clear
gcc -o rr queues.h queues.c OS.h OS.c roundrobin.c criador_processos.c -Wall -pedantic -ansi
time ./rr