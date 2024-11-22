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

void lru(int *arr, int n, const int frames)
{
    int miss = 0, hit = 0;
    int pages[frames];
    int recent[frames];
    for (int i = 0; i < frames; i++)
    {
        pages[i] = -1;
        recent[i] = -1;
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
        int index = findPage(pages, frames, arr[i]);
        if (index != -1)
        {
            hit++;
            recent[index] = i;
        }
        else
        {
            miss++;
            if (pages[j % frames] == -1)
            {
                pages[j % frames] = arr[i];
                recent[j % frames] = i;
                j++;
            }
            else
            {
                int least_recent = __INT_MAX__;
                int least_recent_in = -1;
                for (int r = 0; r < frames; r++)
                {
                    if (recent[r] < least_recent)
                    {
                        least_recent = recent[r];
                        least_recent_in = r;
                    }
                }
                pages[least_recent_in] = arr[i];
                recent[least_recent_in] = i;
            }
        }
    }
    printf("Total Hit:%d \t Total Miss: %d", hit, miss);
}

int main()
{
    int n = 20, frames = 4;
    int arr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    lru(arr, n, frames);
}
