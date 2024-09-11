#include<stdio.h>
struct {
    int id;
    int bt;
    int at;
    int wt;
    int tat;
    int ct;
    int visited;
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
        p[i].id=i;
        printf("Enter burst time for process %d: ",i);
        scanf("%d",&p[i].bt);
        printf("Enter arrival time for process %d: ",i);
        scanf("%d",&p[i].at);
    }
    //sorting
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(p[i].at>p[j].at)
            {   
                p[0]=p[j];
                p[j]=p[i];
                p[i]=p[0];
            }
        }
    }
    printf("GANTT CHART:- \n");
    p[1].wt=0;
    p[1].ct=p[1].bt+p[1].at;
    p[1].tat=p[1].ct-p[1].at;
    double avgtat=p[1].tat,avgwt=p[1].wt;
    printf("%d  P1  %d  ",p[1].at,p[1].ct);
    for(int i=2;i<=n;i++)
    {
        if(p[i-1].ct-p[i].at>0)
        {
            p[i].wt=p[i-1].ct-p[i].at;
        }
        else
        {
            p[i].wt=0;
        }
        p[i].tat=p[i].wt+p[i].bt;
        p[i].ct=p[i].tat+p[i].at;
        printf("P%d  %d  ",i,p[i].ct);
        avgtat+=p[i].tat;
        avgwt+=p[i].wt;
    }
    avgtat/=n;
    avgwt/=n;
    for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                if(p[i].id>p[j].id)
                {   p[0]=p[j];
                    p[j]=p[i];
                    p[i]=p[0];
                }
            }
        }
    printf("\n Prcoess ID | Burst Time | Arrival Time | Waiting Time | Turnaround Time | Completion Time\n");
    for(int i=1;i<=n;i++)
    {
        printf("      ");
        printf("%d",i);
        printf("        ");
        printf("%d",p[i].bt);
        printf("           ");
        printf("%d",p[i].at);
        printf("           ");
        printf("%d",p[i].wt);
        printf("              ");
        printf("%d",p[i].tat);
        printf("              ");
        printf("%d",p[i].ct);
        printf("\n");
    }
    printf("Average waiting time is: %0.1f\n",avgwt);
    printf("Average turnaround time is: %0.1f\n",avgtat);
}
