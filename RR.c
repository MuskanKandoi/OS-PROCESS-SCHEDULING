#include<stdio.h>

typedef struct {
    int id;
    int at;       // Arrival time
    int bt;       // Burst time
    int tat;      // Turnaround time
    int ct;       // Completion time
    int wt;       // Waiting time
    int done;
    int original; // Original burst time
} Pro;

int main() {
    int n, total_time = 0, completed = 0, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Pro pro[n + 1];
    int timeline[100], time_durations[100], timeline_index = 0;

    for (int i = 1; i <= n; i++) {
        pro[i].done = 0;
    }

    for (int i = 1; i <= n; i++) {
        pro[i].id = i;
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &pro[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &pro[i].bt);
        pro[i].original = pro[i].bt;
        printf("\n");
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int queue[100], front = 0, back = 0;
    int current_time = 0;

    for (int i = 1; i <= n; i++) {
        if (pro[i].at == 0) {
            queue[back++] = i;
        }
    }

    while (completed < n) {
        if (front == back) {
            current_time++;
            for (int i = 1; i <= n; i++) {
                if (pro[i].at == current_time) {
                    queue[back++] = i;
                }
            }
            continue;
        }

        int index = queue[front++];
        if (pro[index].bt > quantum) {
            current_time += quantum;
            pro[index].bt -= quantum;
            for (int i = 1; i <= n; i++) {
                if (pro[i].at > current_time - quantum && pro[i].at <= current_time) {
                    queue[back++] = i;
                }
            }
            queue[back++] = index;
            timeline[timeline_index] = pro[index].id;
            time_durations[timeline_index++] = quantum;
        } else {
            current_time += pro[index].bt;
            timeline[timeline_index] = pro[index].id;
            time_durations[timeline_index++] = pro[index].bt;
            pro[index].bt = 0;
            pro[index].ct = current_time;
            pro[index].tat = pro[index].ct - pro[index].at;
            pro[index].wt = pro[index].tat - pro[index].original;
            completed++;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
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
    printf("Process ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time \n");
    float total_tat = 0;
    float total_wt = 0;

    for (int i = 1; i <= n; i++) {
        printf("      %d           %d            %d            %d             %d\n", pro[i].id, pro[i].at, pro[i].original, pro[i].tat, pro[i].wt);
        total_tat += pro[i].tat;
        total_wt += pro[i].wt;
    }

    printf("\nThe average turnaround time is %.2f\n", total_tat / n);
    printf("The average waiting time is %.2f\n", total_wt / n);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < timeline_index; i++) {
        printf(" P%d  ", timeline[i]);
    }
    printf("\n");
    int time = 0;
    printf("0");
    for (int i = 0; i < timeline_index; i++) {
        time += time_durations[i];
        printf("  %d ", time);
    }
    printf("\n");

    return 0;
}
