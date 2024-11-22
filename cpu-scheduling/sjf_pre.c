#include <stdio.h>

struct Process
{
    int p_id;
    int arr_time;
    int burst_time;
    int burst_time_copy;
    int compl_time;
    int tat_time;
    int wait_time;
    int is_comp;
};

void sortByArrivalTime(struct Process *processes, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arr_time > processes[j].arr_time)
            {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sjfPreScheduling(struct Process *processes, int n)
{
    sortByArrivalTime(processes, n);
    int curr_time = processes[0].arr_time;
    int i = 0;
    while (i < n)
    {
        int min_burst_time = __INT_MAX__;
        int min_j = -1;

        for (int j = 0; j < n; j++)
        {
            if (processes[j].arr_time <= curr_time && processes[j].is_comp == 0)
            {
                if (processes[j].burst_time < min_burst_time)
                {
                    min_burst_time = processes[j].burst_time;
                    min_j = j;
                }
            }
        }

        if (min_j == -1)
            curr_time++;

        else
        {
            processes[min_j].burst_time -= 1;
            curr_time++;

            if (processes[min_j].burst_time == 0)
            {
                processes[min_j].compl_time = curr_time;
                processes[min_j].is_comp = 1;
                i++;
                processes[min_j].tat_time = processes[min_j].compl_time - processes[min_j].arr_time;
                processes[min_j].wait_time = processes[min_j].tat_time - processes[min_j].burst_time_copy;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter no of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++)
    {
        processes[i].p_id = i + 1;
        processes[i].is_comp = 0;
        printf("Arrival Time for P%d: ", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].burst_time_copy = processes[i].burst_time;
    }

    sjfPreScheduling(processes, n);

    int avg_tat = 0;
    int avg_wait = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += processes[i].tat_time;
        avg_wait += processes[i].wait_time;
    }

    printf("Avg TAT : %f\nAVG Wait Time: %f", (float)avg_tat / n, (float)avg_wait / n);
}

// 6 2 2 5 8 1 3 0 4 4