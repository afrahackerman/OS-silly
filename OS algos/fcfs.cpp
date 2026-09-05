#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, at, bt, ct, wt, tat, rt;
    bool completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].completed = false;
    }

    int currentTime = 0, completedCount = 0;
    vector<int> sequence;

    while(completedCount < n) {
        int idx = -1;
        int minAT = 1e9;

        // FCFS: pick earliest arrival among available
        for(int i = 0; i < n; i++) {
            if(p[i].at <= currentTime && !p[i].completed) {
                if(p[i].at < minAT) {
                    minAT = p[i].at;
                    idx = i;
                }
            }
        }

        // Idle time handling
        if(idx == -1) {
            sequence.push_back(0); // IDLE
            currentTime++;
        }
        else {
            // execute process fully
            if(currentTime < p[idx].at)
                currentTime = p[idx].at;

            p[idx].rt = currentTime - p[idx].at;  // response time
            currentTime += p[idx].bt;

            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = true;
            sequence.push_back(p[idx].id);
            completedCount++;
        }
    }

    // Output sequence
    cout << "\nExecution Sequence: ";
    for(int id : sequence) {
        if(id == 0) cout << "IDLE ";
        else cout << "P" << id << " ";
    }

    float totalWT = 0, totalTAT = 0, totalRT = 0;

    // Table
    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for(int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalRT += p[i].rt;
    }

    // Averages
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Response Time: " << totalRT / n;

    return 0;
}