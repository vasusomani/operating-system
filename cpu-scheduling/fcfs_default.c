#include <stdio.h>

struct Process
{
    int pId;
    int burst_time;
    int compl_time;
    int wait_time;
    int tat_time;
};

void fcfsScheduling(struct Process *processes, int n)
{
    int curr_time = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].compl_time = curr_time + processes[i].burst_time;
        processes[i].tat_time = processes[i].compl_time;
        processes[i].wait_time = curr_time;

        curr_time = processes[i].compl_time;
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
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &(processes[i].burst_time));
    }

    fcfsScheduling(processes, n);

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