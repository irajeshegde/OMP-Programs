#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int max;
    sscanf(argv[1], "%d", &max);
    int sum = 0;
#pragma omp parallel for
    for (int i = 1; i <= max; i++)
#pragma omp critical
        sum = sum + i;
    printf("%d\n", sum);
    return 0;
}

/*
Commands:
gcc-10 -fopenmp -o sum 6.sum.c
env OMP_NUM_THREADS=8 ./sum 10

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