#include <bits/stdc++.h> 
using namespace std;

struct Process {
    int no, at, bt, ct, tat, wt, rt, pri, temp;
};

struct Process read(int i) {
    struct Process p;
    printf("\nProcess No: %d\n", i);
    p.no = i;
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rt = p.bt;
    printf("Enter Priority: ");
    scanf("%d", &p.pri);
    p.temp = p.pri;
    return p;
}
//FCFS
void FCFS(struct Process p[], int n) {
    int ct = 0;
    float avgwt = 0, avgtat = 0;
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        ct += p[i].bt;
        p[i].ct = ct;
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n, avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}
//SJF
void SJF(struct Process p[], int n) {
    int min_val, min_index;
    float avgwt = 0, avgtat = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
    min_val = p[0].temp, min_index = 0;
    for (int j = 0; j < n && p[j].at <= p[0].at; j++)
        if (p[j].temp < min_val)
            min_val = p[j].temp, min_index = j;
    int i = min_index;
    int c = p[i].ct = p[i].at + 1;
    p[i].rt--;
    if (p[i].rt == 0) {
        p[i].temp = 9999;
    }
    while (1) {
        min_val = 9999, min_index = 0;
        for (int j = 0; j < n && p[j].at <= c; j++)
            if (p[j].temp < min_val)
                min_val = p[j].temp, min_index = j;
        i = min_index;
        p[i].ct = c = c + 1;
        p[i].rt--;
        if (p[i].rt == 0) {
            p[i].temp = 9999;
        }
        int remaining = 0;
        for (int j = 0; j < n; j++)
            if (p[j].rt != 0)
                remaining++;
        if (remaining == 0)
            break;
    }
    printf("\nProcess\t\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n, avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}
//SRTF
void SRTF(struct Process p[], int n) {
    int time = 0, remain = n;
    float avgwt = 0, avgtat = 0;
    printf("\nProcess\t\tAT\tBT\tCT\tTAT\tWT\n");
    while (remain != 0) {
        int s = -1;
        int min_rt = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt < min_rt && p[i].rt > 0) {
                s = i;
                min_rt = p[i].rt;
            }
        }
        if (s == -1) {
            time++;
            continue;
        }
        p[s].rt--;
        if (p[s].rt == 0) {
            remain--;
            p[s].ct = time + 1;
            p[s].tat = p[s].ct - p[s].at;
            avgtat += p[s].tat;
            p[s].wt = p[s].tat - p[s].bt;
            avgwt += p[s].wt;
            printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[s].no, p[s].at, p[s].bt, p[s].ct, p[s].tat, p[s].wt);
        }
        time++;
    }
    avgtat /= n, avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}
//Round Robin
void RR(struct Process p[], int n, int tq) {
    int ct = 0, flag = 0, remaining = n;
    float avgwt = 0, avgtat = 0;
    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWT\n");
    while (1) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                done = false;
                if (p[i].rt > tq) {
                    ct += tq;
                    p[i].rt -= tq;
                } else {
                    ct += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = ct;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
                    avgwt += p[i].wt;
                    avgtat += p[i].tat;
                    remaining--;
                }
            }
        }
        if (done) break;
    }
    avgtat /= n, avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}
//PriorityScheduling
void PriorityScheduling(struct Process p[], int n) {
    int remaining = n;
    float avgwt = 0, avgtat = 0;
    printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; remaining > 0;) {
        int min_val = 9999, min_index = 0;
        for (int j = 0; j < n; j++)
            if (p[j].temp < min_val && p[j].at <= p[i].ct) {
                min_val = p[j].temp, min_index = j;
            }
        i = min_index;
        p[i].ct = p[i].ct + 1;
        p[i].rt--;
        if (p[i].rt == 0) {
            p[i].temp = 9999;
            remaining--;
        }
    }
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n, avgwt /= n;
    printf("\nAverage TurnAroundTime=%f\nAverage WaitingTime=%f", avgtat, avgwt);
}

int main() {
    int choice;
    printf("Number of Processes: ");
    int n;
    scanf("%d", &n);
    struct Process p[n];
    printf("Process Ids:\n");
    for (int i = 0; i < n; i++)
        p[i] = read(i + 1);
    printf("Time Quantum: ");
    int tq;
    scanf("%d", &tq);
    printf("Press 1 to get FCFS\nPress 2 to get SJF\nPress 3 to get SRTF\nPress 4 to get RR\nPress 5 to get Priority Scheduling\nPress 6 to get Thank you\nPress 7 to exit\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            FCFS(p, n);
            break;
        case 2:
            SJF(p, n);
            break;
        case 3:
            SRTF(p, n);
            break;
        case 4:
            RR(p, n, tq);
            break;
        case 5:
            PriorityScheduling(p, n);
            break;
        case 6:
            printf("Thank you\n");
            break;
        case 7:
            return 0;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}
