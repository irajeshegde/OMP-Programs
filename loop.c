#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/Cellar/libomp/11.0.0/include/omp.h"

int main(int argc, char *argv[])
{
    int max;
    sscanf(argv[1], "%d", &max);
#pragma omp parallel for
    for (int i = 1; i <= max; i++)
        printf("%d -> %d\n", omp_get_thread_num(), i);
    return 0;
}
/*
Commands:
gcc-10 -fopenmp -o loop loop.c
env OMP_NUM_THREADS=8 ./loop 10

Output:
0 -> 1
0 -> 2
2 -> 5
1 -> 3
1 -> 4
3 -> 6
4 -> 7
5 -> 8
6 -> 9
7 -> 10
*/