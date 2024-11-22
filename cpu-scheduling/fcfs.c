#include <stdio.h>

struct Process
{
    int p_id;
    int arr_time;
    int burst_time;
    int compl_time;
    int tat_time;
    int wait_time;
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

void fcfsScheduling(struct Process *processes, int n)
{
    sortByArrivalTime(processes, n);
    int curr_time = 0;
    int i = 0;
    while (i < n)
    {
        if (processes[i].arr_time <= curr_time)
        {
            processes[i].compl_time = curr_time + processes[i].burst_time;
            processes[i].tat_time = processes[i].compl_time - processes[i].arr_time;
            processes[i].wait_time = processes[i].tat_time - processes[i].burst_time;
            curr_time = processes[i].compl_time;
            i++;
        }
        else
        {
            curr_time = processes[i].arr_time;
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
        printf("Arrival Time for P: %d", i + 1);
        scanf("%d", &processes[i].arr_time);
        printf("Burst Time for P: %d", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    fcfsScheduling(processes, n);

    int avg_tat = 0;
    int avg_wait = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += processes[i].tat_time;
        avg_wait += processes[i].wait_time;
    }

    printf("Avg TAT : %f\nAVG Wait Time: %f", (float)avg_tat / n, (float)avg_wait / n);
}