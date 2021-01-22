#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
const int MAX = 1024;

void insert_sort(long *sort, int c, long val)
{
    int i = 0;

    sort[c] = val;
    if (c == 0)
        return;
    for (i = c; i > 0; i--)
    {
        if (val > sort[i - 1])
            sort[i] = sort[i - 1];
        else
            break;
    }
    sort[i] = val;
}

int main(int nargs, char *args[])
{
    int temp[10], size, rank, gath_buf[10];
    FILE *infile = NULL;
    long sort[1024];
    long val;
    int c = 0;
    int err, tot, i = 0;
    MPI_Init(&nargs, &args);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    infile = fopen("p1.txt", "r");
    if (NULL == infile)
    {
        perror("fopen");
        return -1;
    }

    err = MPI_Scatter(&infile, 1, MPI_INT, &tot, 1, MPI_INT, 0, MPI_COMM_WORLD);

    while (!feof(infile))
    {
        fscanf(infile, "%ld\n", &val);
        insert_sort(sort, c, val);
        ++c;
    }

    for (i = 0; i < c; i++)
    {
        temp[i] = sort[i];
    }

    err = MPI_Gather(&temp, 1, MPI_INT, &gath_buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Result - Descending order of loan amount\n");
        for (i = 0; i < c; i++)
        {
            printf("%ld \n", sort[i]);
        }
    }

    if (infile)
    {
        fclose(infile);
        infile = NULL;
    }
    MPI_Finalize();
    return 0;
}