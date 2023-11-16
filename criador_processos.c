#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N_PROCESSOS 3


int main()
{
    FILE *f_ptr;
    int i;
    srand(time(NULL));



    f_ptr = fopen("processos.txt","w");
    /*definir numero de processos*/
    
    for(i=0;i<N_PROCESSOS;i++)
    {
        
    }
    fclose(f_ptr);
    return 0;
}