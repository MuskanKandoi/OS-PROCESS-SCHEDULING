#include <stdio.h>
typedef struct {
    int pid;             
    int bt; 
    int at;               
    int wt;               
    int tat;              
    int ct;               
    int visited;         
} Process;
int main() {
    int n;  
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n + 1];  
    for (int i = 1; i <= n; i++) {
        p[i].pid = i;
        printf("Enter Burst Time and Arrival Time for Process %d: ", i);
        scanf("%d %d", &p[i].bt, &p[i].at);
        p[i].visited = 0; 
    }
    int i, completed = 0, t = 0, min_bt, idx;
    double avg_wt = 0.0, avg_tat = 0.0;
    int order[n + 1];
    int order_index = 0;
    printf("GANTT CHART:\n");
    while (completed != n) {
        idx = -1;
        min_bt = 9999;
        for (i = 1; i <= n; i++) {
            if (p[i].at <= t && !p[i].visited && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            t++;
            continue;
        }
        t += p[idx].bt; 
        p[idx].ct = t;  
        p[idx].wt = t - p[idx].bt - p[idx].at;
        p[idx].tat = t - p[idx].at; 
        avg_wt += p[idx].wt;
        avg_tat += p[idx].tat;
        p[idx].visited = 1;
        order[order_index++] = p[idx].pid; 
        completed++;
    }
    for (i = 0; i < order_index; i++) {
        printf(" P%d  ", order[i]);
    }
    printf("\n");
    printf("0   ");
    for (i = 0; i < order_index; i++) {
        printf("%d   ", p[order[i]].ct);
    }
    printf("\n");
    printf("\n Prcoess ID | Burst Time | Arrival Time | Waiting Time | Turnaround Time | Completion Time\n");
    for(int i=1;i<=n;i++)
    {
        printf("      ");
        printf("%d",i);
        printf("           ");
        printf("%d",p[i].bt);
        printf("            ");
        printf("%d",p[i].at);
        printf("             ");
        printf("%d",p[i].wt);
        printf("                ");
        printf("%d",p[i].tat);
        printf("                ");
        printf("%d",p[i].ct);
        printf("\n");
    }
    printf("Avg WT: %.1f\n", avg_wt / n);
    printf("Avg TAT: %.1f\n", avg_tat / n);
    return 0;
}
