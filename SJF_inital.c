#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_remaining_time = INT_MAX;
    int index = -1;
    
    for (int i = 0; i < n; i++) {
        // Select process that has arrived and has not been completed yet
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed && 
                proc[i].remaining_time < min_remaining_time) {
            min_remaining_time = proc[i].remaining_time;
            index = i;
        }
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
        int current_time = 0;
    int completed = 0;
    
    // Initialize the remaining time for all processes to their burst time
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0; // Mark all processes as not completed
    }

    printf("Execution Order: ");
    while (completed < n) {
        // Find the process with the shortest remaining time
        int idx = findNextProcess(proc, current_time);
        
        if (idx == -1) {
            // No process is ready at the current time, just increment the time
            current_time++;
            continue;
        }
        
        // Execute the selected process
        printf("P%d ", proc[idx].process_id);
        proc[idx].remaining_time--;  // Decrease the remaining time
        current_time++;             // Increment the time by 1 unit

        // If process is completed, calculate its turnaround time and waiting time
        if (proc[idx].remaining_time == 0) {
            proc[idx].is_completed = 1;
            completed++;
            proc[idx].turnaround_time = current_time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
        }
    }
    printf("\n");
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
                proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
