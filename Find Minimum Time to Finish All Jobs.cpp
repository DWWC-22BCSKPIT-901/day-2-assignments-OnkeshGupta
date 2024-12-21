#include <bits/stdc++.h>

using namespace std;

bool isFeasible(vector<int>& jobs, vector<int>& workers, int idx, int maxTime) {
    if (idx == jobs.size()) return true;

    for (int i = 0; i < workers.size(); ++i) {
        if (workers[i] + jobs[idx] <= maxTime) {
            workers[i] += jobs[idx];
            if (isFeasible(jobs, workers, idx + 1, maxTime)) return true;
            workers[i] -= jobs[idx];
        }

        if (workers[i] == 0) break;
    }

    return false;
}

int findMinimumTime(vector<int>& jobs, int k) {
    sort(jobs.rbegin(), jobs.rend());

    int left = jobs[0], right = accumulate(jobs.begin(), jobs.end(), 0), result = right;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        vector<int> workers(k, 0);

        if (isFeasible(jobs, workers, 0, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    int n, k;
    cout << "Enter the number of jobs: ";
    cin >> n;

    vector<int> jobs(n);
    cout << "Enter the time required for each job: ";
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i];
    }

    cout << "Enter the number of workers: ";
    cin >> k;

    int result = findMinimumTime(jobs, k);
    cout << "The minimum possible maximum working time is: " << result << endl;

    return 0;
}