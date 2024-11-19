#include <stdio.h>

struct Process
{
    int pId;
    int arr_time;
    int burst_time;
    int burst_time_copy;
    int compl_time;
    int wait_time;
    int tat_time;
    int rem_time;
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

void roundRobinScheduling(struct Process *processes, int n, int quantum)
{
    int curr_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].rem_time > 0 && processes[i].arr_time <= curr_time)
            {
                flag = 1;
                if (processes[i].rem_time > quantum)
                {
                    curr_time += quantum;
                    processes[i].rem_time -= quantum;
                }
                else
                {
                    curr_time += processes[i].rem_time;
                    processes[i].rem_time = 0;
                    processes[i].is_completed = 1;
                    completed++;

                    processes[i].compl_time = curr_time;
                    processes[i].tat_time = processes[i].compl_time - processes[i].arr_time;
                    processes[i].wait_time = processes[i].tat_time - processes[i].burst_time;
                }
            }
        }
        if (flag == 0)
            curr_time++;
    }
}

int main()
{
    int n, quantum;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    struct Process processes[n];
    float avg_tat = 0, avg_wait = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].pId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &(processes[i].arr_time));
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &(processes[i].burst_time));
        processes[i].burst_time_copy = processes[i].burst_time;
        processes[i].rem_time = processes[i].burst_time;
        processes[i].is_completed = 0;
    }

    sortByArrivalTime(processes, n);
    roundRobinScheduling(processes, n, quantum);

    for (int i = 0; i < n; i++)
    {
        avg_tat += processes[i].tat_time;
        avg_wait += processes[i].wait_time;
        printf("Process %d\nCompl Time: %d\nTAT Time: %d\nWait Time: %d\n\n",
               processes[i].pId, processes[i].compl_time, processes[i].tat_time, processes[i].wait_time);
    }

    avg_tat /= n;
    avg_wait /= n;

    printf("Avg TAT: %.2f\n", avg_tat);
    printf("Avg Wait Time: %.2f\n", avg_wait);
    
    return 0;
}