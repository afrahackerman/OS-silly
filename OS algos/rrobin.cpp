#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt;
    int rem_bt;
    int ct, tat, wt, rt;
    bool started = false;
    bool added = false;
};

int main() {

    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;

        cout << "Enter AT and BT for P" << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;

        p[i].rem_bt = p[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;

    int currentTime = 0;
    int completed = 0;

    vector<int> gantt;

    // Add first arriving processes
    for(int i = 0; i < n; i++) {
        if(p[i].at == 0) {
            q.push(i);
            p[i].added = true;
        }
    }

    while(completed < n) {

        // If queue empty → CPU idle
        if(q.empty()) {

            gantt.push_back(0);
            currentTime++;

            // check new
            for(int i = 0; i < n; i++) {
                if(!p[i].added && p[i].at <= currentTime) {
                    q.push(i);
                    p[i].added = true;
                }
            }

            continue;
        }

        int idx = q.front();
        q.pop();

        // Rt
        if(!p[idx].started) {
            p[idx].rt = currentTime - p[idx].at;
            p[idx].started = true;
        }

        // Execute
        int execTime = min(tq, p[idx].rem_bt);

        for(int t = 0; t < execTime; t++) {

            gantt.push_back(p[idx].id);

            currentTime++;
            p[idx].rem_bt--;

            // newly arrived processes during execution
            for(int i = 0; i < n; i++) {
                if(!p[i].added && p[i].at <= currentTime) {
                    q.push(i);
                    p[i].added = true;
                }
            }

            // p completed during execution
            if(p[idx].rem_bt == 0)
                break;
        }

        // If completed
        if(p[idx].rem_bt == 0) {

            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            completed++;
        }
        else {
            //back in queue
            q.push(idx);
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

    float totalWT = 0;
    float totalTAT = 0;
    float totalRT = 0;

    for(int i = 0; i < n; i++) {

        cout << left
             << setw(6) << ("P" + to_string(p[i].id))
             << setw(6) << p[i].at
             << setw(6) << p[i].bt
             << setw(6) << p[i].ct
             << setw(8) << p[i].tat
             << setw(6) << p[i].wt
             << setw(6) << p[i].rt
             << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalRT += p[i].rt;
    }


    cout << fixed << setprecision(2);

    cout << "\nAverage WT  = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;
    cout << "\nAverage RT  = " << totalRT / n;

    // Gantt 
    cout << "\n\nGantt Chart:\n0";

    for(int i = 0; i < gantt.size(); i++) {

        if(gantt[i] == 0)
            cout << " | IDLE | " << i + 1;
        else
            cout << " | P" << gantt[i] << " | " << i + 1;
    }

    cout << endl;

    return 0;
}