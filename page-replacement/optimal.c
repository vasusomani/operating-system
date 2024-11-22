#include <stdio.h>
#include <stdlib.h>

int findPage(int *arr, int n, int k, int from)
{
    for (int i = from; i < n; i++)
    {
        if (arr[i] == k)
            return i;
    }
    return -1;
}

void optimal(int *arr, int n, int frames)
{
    int pages[frames];
    int hit = 0, miss = 0;
    for (int i = 0; i < frames; i++)
        pages[i] = -1;

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

        int index = findPage(pages, frames, arr[i], 0);
        if (index != -1)
        {
            hit++;
        }
        else
        {
            miss++;
            // Empty slots are there
            if (pages[j % frames] == -1)
            {
                pages[j % frames] = arr[i];
                j++;
            }
            else
            {
                // Find farthest point
                int max_value = -1;
                int max_k = -1;
                for (int k = 0; k < frames; k++)
                {
                    int new_index = findPage(arr, n, pages[k], i + 1);
                    if (new_index == -1)
                    {
                        pages[k] = arr[i];
                        max_k = -1;
                        j++;
                        break;
                    }
                    if (max_value < new_index)
                    {
                        max_value = new_index;
                        max_k = k;
                    }
                }
                if (max_k != -1)
                {
                    pages[max_k] = arr[i];
                    j++;
                }
            }
        }
    }
    printf("Total Hit: %d\nTotal Miss: %d", hit, miss);
}

int main()
{
    int n = 20, frames = 4;
    int arr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    optimal(arr, n, frames);
    return 0;
}