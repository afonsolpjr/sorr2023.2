clear
gcc -o rr queues.h queues.c OS.h OS.c roundrobin.c -Wall -pedantic -ansi
time ./rr