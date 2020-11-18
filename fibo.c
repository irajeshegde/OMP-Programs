#include <stdio.h>
#include "/usr/local/Cellar/libomp/11.0.0/include/omp.h"

long fib(int n)
{
    return (n < 2 ? 1 : fib(n - 1) + fib(n - 2));
}

int main()
{
    int n = 45;
#pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("%d -> %ld \n", t, fib(n + t));
    }
    return 0;
}
/*
Commands:
gcc-10 -fopenmp -O2 -o fibo fibo.c
env OMP_NUM_THREADS=16 time ./fibo 

Output:
0 -> 1836311903 
1 -> 2971215073 
18.20 real        29.22 user         0.06 sys
*/