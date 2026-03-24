#include <stdio.h>
#include <limits.h>

struct Process{    
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

int main(){
    int n, completed = 0, time = 0;
    float totalWT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++){
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].pid = i + 1;
        processes[i].rt = processes[i].bt;
    }

    while (completed != n){
        int shortest = -1;
        int minRT = INT_MAX;

        for (int i = 0; i < n; i++){
            if (processes[i].at <= time && processes[i].rt > 0 && processes[i].rt < minRT){
                minRT = processes[i].rt;
                shortest = i;
            }
        }
        if (shortest == -1){
            time ++;
            continue;
        }
        processes[shortest].rt --;
        if (processes[shortest].rt == 0){
            processes[shortest].ct = time + 1;
            processes[shortest].tat = processes[shortest].ct - processes[shortest].at;
            processes[shortest].wt = processes[shortest].tat - processes[shortest].bt;
            totalWT += processes[shortest].wt;
            completed ++;
        }
        time ++;
    }
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    return 0;   
}