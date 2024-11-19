#include <stdio.h>

struct Process
{
    int pId;
    int arr_time;
    int burst_time;
    int priority;
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

void priorityNonPreScheduling(struct Process *processes, int n)
{
    sortByArrivalTime(processes, n);

    int curr_time = processes[0].arr_time;
    int p_compl = 0;

    while (p_compl != n)
    {
        int max_priority = -1;
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

        processes[max_i].compl_time = curr_time + processes[max_i].burst_time;
        processes[max_i].tat_time = processes[max_i].compl_time - processes[max_i].arr_time;
        processes[max_i].wait_time = processes[max_i].tat_time - processes[max_i].burst_time;
        processes[max_i].is_completed = 1;
        p_compl++;

        curr_time = processes[max_i].compl_time;
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
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &(processes[i].arr_time));
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &(processes[i].burst_time));
        printf("Enter priority for process %d (Higher number higher priority): ", i + 1);
        scanf("%d", &(processes[i].priority));
        processes[i].is_completed = 0;
    }

    priorityNonPreScheduling(processes, n);

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