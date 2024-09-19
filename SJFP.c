#include<stdio.h>

typedef struct {
    int id;        // Process ID
    int at;        // Arrival time
    int bt;        // Burst time
    int tat;       // Turnaround time
    int finish;    // Completion time
    int wait;      // Waiting time
    int done;
    int start_bt;  // Original burst time
} Pro;

int main() {
    int num_procs, total_time = 0, completed = 0, time_slice;
    printf("Enter the number of processes: ");
    scanf("%d", &num_procs);
    
    Pro pro[num_procs + 1];
    int timeline[100], slice_times[100], timeline_index = 0;

    for (int i = 1; i <= num_procs; i++) {
        pro[i].done = 0;
    }

    for (int i = 1; i <= num_procs; i++) {
        pro[i].id = i;
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &pro[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &pro[i].bt);
        pro[i].start_bt = pro[i].bt;
        printf("\n");
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_slice);

    int queue[100], front = 0, back = 0;
    int current_time = 0;

    for (int i = 1; i <= num_procs; i++) {
        if (pro[i].at == 0) {
            queue[back++] = i;
        }
    }

    while (completed < num_procs) {
        if (front == back) {
            current_time++;
            for (int i = 1; i <= num_procs; i++) {
                if (pro[i].at == current_time) {
                    queue[back++] = i;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (pro[idx].bt > time_slice) {
            current_time += time_slice;
            pro[idx].bt -= time_slice;
            for (int i = 1; i <= num_procs; i++) {
                if (pro[i].at > current_time - time_slice && pro[i].at <= current_time) {
                    queue[back++] = i;
                }
            }
            queue[back++] = idx;
            timeline[timeline_index] = pro[idx].id;
            slice_times[timeline_index++] = time_slice;
        } else {
            current_time += pro[idx].bt;
            timeline[timeline_index] = pro[idx].id;
            slice_times[timeline_index++] = pro[idx].bt;
            pro[idx].bt = 0;
            pro[idx].finish = current_time;
            pro[idx].tat = pro[idx].finish - pro[idx].at;
            pro[idx].wait = pro[idx].tat - pro[idx].start_bt;
            completed++;
        }
    }

    for (int i = 1; i <= num_procs; i++) {
        for (int j = i + 1; j <= num_procs; j++) {
            if (pro[i].id > pro[j].id) {
                Pro temp = pro[j];
                pro[j] = pro[i];
                pro[i] = temp;
            }
        }
    }

    printf("\n");
    for (int i = 0; i <= 20; i++) {
        printf("--");
    }
    printf("\n");
    printf("id     at      bt      tat     wt\n");

    float total_tat = 0;
    float total_wt = 0;

    for (int i = 1; i <= num_procs; i++) {
        printf("%d      %d       %d       %d       %d\n", pro[i].id, pro[i].at, pro[i].start_bt, pro[i].tat, pro[i].wait);
        total_tat += pro[i].tat;
        total_wt += pro[i].wait;
    }

    printf("\nThe average turnaround time is %.2f\n", total_tat / num_procs);
    printf("The average waiting time is %.2f\n", total_wt / num_procs);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < timeline_index; i++) {
        printf("| P%d ", timeline[i]);
    }
    printf("|\n");
    
    int time = 0;
    printf("0");
    for (int i = 0; i < timeline_index; i++) {
        time += slice_times[i];
        printf("   %d", time);
    }
    printf("\n");

    return 0;
}
