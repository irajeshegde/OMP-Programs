#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
#pragma omp parallel num_threads(2)
    {
#pragma omp single printf("read input\n");
        printf("compute results\n");
#pragma omp single printf("write output\n");
    }
}

/*
Commands:
gcc-10 -fopenmp -o hello 1.hello.c
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