#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    int all_done;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
    }

    printf("Execution Order: ");

    while (completed < n) {
        all_done = 1;

        for (int i = 0; i < n; i++) {
            // Process only if arrived and not finished
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                all_done = 0;

                int slice = (proc[i].remaining_time > quantum) ? quantum : proc[i].remaining_time;
                printf("P%d ", proc[i].process_id);

                proc[i].remaining_time -= slice;
                current_time += slice;

                // If process finishes, calculate waiting & turnaround
                if (proc[i].remaining_time == 0) {
                    proc[i].turnaround_time = current_time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                    completed++;
                }
            }
        }

        // If no process ready, move time forward
        if (all_done) {
            current_time++;
        }
    }

    printf("\n\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    // Calculate the turnaround time after the scheduling
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
                proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling


    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
