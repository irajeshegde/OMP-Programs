#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/Cellar/libomp/11.0.0/include/omp.h"

int main(int argc, char *argv[])
{
#pragma omp parallel
    {
        printf("Hello World from thread -> %d\n", omp_get_thread_num());
    }
}

/*
Commands:
gcc-10 -fopenmp -o hello hello.c
env OMP_NUM_THREADS=8 ./hello

Output:
Hello World from thread -> 2
Hello World from thread -> 1
Hello World from thread -> 3
Hello World from thread -> 4
Hello World from thread -> 5
Hello World from thread -> 6
Hello World from thread -> 7
Hello World from thread -> 0
*/