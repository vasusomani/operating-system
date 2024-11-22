#include <stdio.h>

void BestFit(int *blocks, int n_blocks, int *processes, int n_processes)
{
    for (int i = 0; i < n_processes; i++)
    {
        int allocated = 0;
        int min_wastage = __INT_MAX__;
        int min_j = -1;
        for (int j = 0; j < n_blocks; j++)
        {
            int wastage = blocks[j] - processes[i];
            if (wastage< min_wastage && wastage>=0){
                min_wastage = wastage;
                min_j = j;
            }
        }
        if (min_j!=-1)
        {
            blocks[min_j] -= processes[i];
            printf("Process %d of size %d allocated to Block %d of size %d\n", i + 1, processes[i], min_j + 1, blocks[min_j]);
        }
        else
        {
            printf("Process %d of size %d not allocated\n", i + 1, processes[i]);
        }
    }
}

int main()
{
    int n_blocks = 5, n_processes = 4;
    int blocks[] = {100, 500, 200, 300, 600};
    int processes[] = {212, 417, 112, 426};

    BestFit(blocks, n_blocks, processes, n_processes);
}