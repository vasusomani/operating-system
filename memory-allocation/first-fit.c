#include <stdio.h>

void FirstFit(int *blocks, int n_blocks, int *processes, int n_processes)
{
    for (int i = 0; i < n_processes; i++)
    {
        int allocated = 0;
        for (int j = 0; j < n_blocks; j++)
        {
            if (blocks[j] >= processes[i])
            {
                printf("Process %d of size %d allocated to Block %d of size %d\n", i + 1, processes[i], j + 1, blocks[j]);
                blocks[j] -= processes[i];
                allocated = 1;
                break;
            }
        }
        if (allocated == 0)
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

    FirstFit(blocks, n_blocks, processes, n_processes);
}