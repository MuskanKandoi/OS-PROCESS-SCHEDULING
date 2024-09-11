#include<stdio.h>
struct {
    int bt;
    int wt;
    int tat;
    int ct;
}p[10];

int main()
{
    int tt=0;
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        printf("Process %d\n",i);
        printf("Enter burst time for process %d: ",i);
        scanf("%d",&p[i].bt);
    }
    printf("GANTT CHART:- \n");
    p[1].wt=0;
    p[1].ct=p[1].bt;
    tt=p[1].bt;
    p[1].tat=p[1].ct;
    double avgtat=p[1].tat,avgwt=0.0;
    printf("0  P1  %d  ",p[1].ct);
    for(int i=2;i<=n;i++)
    {
        p[i].wt=tt;
        p[i].tat=p[i].wt+p[i].bt;
        p[i].ct=p[i].tat;
        tt+=p[i].bt;
        printf("P%d  %d  ",i,p[i].ct);
        avgtat+=p[i].tat;
        avgwt+=p[i].wt;
    }
    avgtat/=n;
    avgwt/=n;
    printf("\n Prcoess ID | Burst Time | Waiting Time | Turnaround Time | Completion Time\n");
    for(int i=1;i<=n;i++)
    {
        printf("      ");
        printf("%d",i);
        printf("            ");
        printf("%d",p[i].bt);
        printf("            ");
        printf("%d",p[i].wt);
        printf("                ");
        printf("%d",p[i].tat);
        printf("                 ");
        printf("%d",p[i].ct);
        printf("\n");
    }
    printf("Average waiting time is: %0.1f\n",avgwt);
    printf("Average turnaround time is: %0.1f\n",avgtat);
}
