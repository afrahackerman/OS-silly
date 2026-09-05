#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, remainingTime, wt, tat, ct, rt;
    bool started = false;
};

int main() {
    int n, currentTime = 0, completed = 0;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    vector<int> gantt;


    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter AT and BT for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].remainingTime = p[i].bt;
    }

    // SRTF logic
    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remainingTime > 0 &&
               (idx == -1 || p[i].remainingTime < p[idx].remainingTime)) {
                idx = i;
            }
        }

        if (idx != -1) {

            if (!p[idx].started) {
                p[idx].rt = currentTime - p[idx].at;
                p[idx].started = true;
            }

            p[idx].remainingTime--;
            gantt.push_back(p[idx].id);
            currentTime++;

            if (p[idx].remainingTime == 0) {
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        } else {
            gantt.push_back(0);
            currentTime++;
        }
    }


    cout << "\n\n";
    cout << left
         << setw(6) << "PID"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "CT"
         << setw(8) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT" << endl;

    cout << "---------------------------------------------\n";

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    
    for (auto &proc : p) {
        cout << left
             << setw(6) << ("P" + to_string(proc.id))
             << setw(6) << proc.at
             << setw(6) << proc.bt
             << setw(6) << proc.ct
             << setw(8) << proc.tat
             << setw(6) << proc.wt
             << setw(6) << proc.rt
             << endl;

        totalWT += proc.wt;
        totalTAT += proc.tat;
        totalRT += proc.rt;
    }

  
    cout << fixed << setprecision(2);
    cout << "\nAverage WT  = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage RT  = " << totalRT / n;


    cout << "\n\nGantt Chart:\n0";
    for (int i = 0; i < gantt.size(); i++) {
        if (gantt[i] == 0)
            cout << " | IDLE | " << i + 1;
        else
            cout << " | P" << gantt[i] << " | " << i + 1;
    }
    cout << endl;

    return 0;
}