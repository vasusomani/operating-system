#include <stdio.h>
#include <stdlib.h>

int findPage(int *arr, int n, int k)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == k)
            return i;
    }
    return -1;
}

void fifo(int *arr, int n, int frames)
{
    int miss = 0, hit = 0;
    int pages[frames];
    for (int i = 0; i < frames; i++)
    {
        pages[i] = -1;
    }

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < frames; k++)
        {
            if (pages[k] == -1)
                printf(" ");
            else
                printf("%d ", pages[k]);
        }
        printf("\n");

        if (findPage(pages, frames, arr[i]) != -1)
        {
            hit++;
        }
        else
        {
            miss++;
            pages[(j++) % frames] = arr[i];
        }
    }
    printf("Total Hit:%d \t Total Miss: %d", hit, miss);
}

int main()
{
    int n = 15, frames = 3;
    int arr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};
    fifo(arr, n, frames);
}
