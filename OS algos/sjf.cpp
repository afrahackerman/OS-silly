#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt, rt;
    bool completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // ✅ Improved Input (AT + BT together)
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter AT and BT for P" << p[i].pid << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].completed = false;
    }

    int time = 0, completed = 0;
    vector<int> gantt;

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        // SJF selection
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        // idle case
        if (idx == -1) {
            time++;
            continue;
        }

        // execute
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].rt = p[idx].wt;

        p[idx].completed = true;
        completed++;

        gantt.push_back(p[idx].pid);
    }

    // Output
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << endl;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].rt;
    }

    // Gantt
    cout << "\nGantt Chart:\n| ";
    for (int id : gantt) {
        cout << "P" << id << " | ";
    }
    cout << endl;

    // Averages
    cout << "\nAverage WT = " << total_wt / n;
    cout << "\nAverage TAT = " << total_tat / n;
    cout << "\nAverage RT = " << total_rt / n;

    return 0;
}