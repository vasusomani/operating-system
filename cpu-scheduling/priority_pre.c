#include <stdio.h>

struct Process
{
    int pId;
    int arr_time;
    int burst_time;
    int priority;
    int burst_time_copy;
    int compl_time;
    int wait_time;
    int tat_time;
    int is_completed;
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

void priorityPreScheduling(struct Process *processes, int n)
{
    sortByArrivalTime(processes, n);

    int curr_time = processes[0].arr_time;
    int p_compl = 0;

    while (p_compl != n)
    {
        int max_priority = 0;
        int max_i = -1;

        for (int i = 0; i < n; i++)
        {
            if (curr_time >= processes[i].arr_time && processes[i].is_completed == 0)
            {
                if (processes[i].priority > max_priority)
                {
                    max_priority = processes[i].priority;
                    max_i = i;
                }
            }
        }

        if (max_i == -1)
        {
            curr_time++;
            continue;
        }

        processes[max_i].burst_time = processes[max_i].burst_time - 1;
        curr_time++;

        if (processes[max_i].burst_time == 0)
        {
            processes[max_i].compl_time = curr_time;
            processes[max_i].is_completed = 1;
            p_compl++;
            processes[max_i].tat_time = processes[max_i].compl_time - processes[max_i].arr_time;
            processes[max_i].wait_time = processes[max_i].tat_time - processes[max_i].burst_time_copy;
        }
    }
}

int main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    float avg_tat = 0;
    float avg_wait = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].pId = i + 1;
        printf("Enter arrival time: ");
        scanf("%d", &(processes[i].arr_time));
        printf("Enter burst time: ");
        scanf("%d", &(processes[i].burst_time));
        printf("Enter priority (Higher number higher priority): ");
        scanf("%d", &(processes[i].priority));
        processes[i].is_completed = 0;
        processes[i].burst_time_copy = processes[i].burst_time;
    }

    priorityPreScheduling(processes, n);

    for (int i = 0; i < n; i++)
    {
        avg_tat += processes[i].tat_time;
        avg_wait += processes[i].wait_time;
        printf("Process %d\nCompl Time: %d\nTAT Time: %d\nWait Time: %d\n\n", processes[i].pId, processes[i].compl_time, processes[i].tat_time, processes[i].wait_time);
    }

    avg_tat /= n;
    avg_wait /= n;

    printf("Avg TAT: %f\n", avg_tat);
    printf("Avg Wait Time: %f\n", avg_wait);
}