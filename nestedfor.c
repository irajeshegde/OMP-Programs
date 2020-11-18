#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/Cellar/libomp/11.0.0/include/omp.h"

int main(int argc, char *argv[])
{
    int max;
    sscanf(argv[1], "%d", &max);
    //making two for loops parallel
#pragma omp parallel for collapse(2)
    for (int i = 1; i <= max; i++)
        for (int j = 1; j <= max; j++)
            printf("%d -> (%d, %d)\n", omp_get_thread_num(), i, j);
    return 0;
}
/*
Commands:
gcc-10 -fopenmp -o nested nestedfor.c
env OMP_NUM_THREADS=8 ./nested 10

Output:
*/