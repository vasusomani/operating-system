#include <stdio.h>
#include <stdbool.h>
#define P 5 // Number of processes
#define R 3 // Number of resources

void banker(int avail[R], int need[P][R], int allot[P][R])
{
    int alloted[P] = {0};
    int allotCount = 0;
    while (allotCount < P)
    {
        bool allocatedInThisPass = false;
        for (int i = 0; i < P; i++)
        {
            if (alloted[i] == 0)
            {
                bool canAllocate = 1;
                for (int j = 0; j < R; j++)
                {
                    if (avail[j] < need[i][j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < R; j++)
                    {
                        avail[j] += allot[i][j];
                    }
                    alloted[i] = 1;
                    allotCount++;
                    allocatedInThisPass = true;
                    printf("-> P%d ", i);
                }
            }
        }
        if (!allocatedInThisPass)
        {
            printf("\nSystem is not in a safe state\n");
            return;
        }
    }
    printf("\nSystem is in safe state\n");
}

int main()
{
    int allot[P][R] = {// Allocated resources
                       {0, 1, 0},
                       {2, 0, 0},
                       {3, 0, 2},
                       {2, 1, 1},
                       {0, 0, 2}};
    int req[P][R] = {// Required resources
                     {7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};
    int avail[R] = {3, 3, 2}; // Available resources
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = req[i][j] - allot[i][j];

    banker(avail, need, allot);
    return 0;
}
