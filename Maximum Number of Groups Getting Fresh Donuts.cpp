#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;
class DonutShop {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> remainderCount(batchSize, 0);
        for (int group : groups) {
            remainderCount[group % batchSize]++;
        }

        int happyGroups = remainderCount[0];  
        remainderCount[0] = 0;

        for (int i = 1, j = batchSize - 1; i <= j; i++) {
            if (i == j) {
                happyGroups += remainderCount[i] / 2;  
            } else {
                int pairs = min(remainderCount[i], remainderCount[j]);
                happyGroups += pairs;
                remainderCount[i] -= pairs;
                remainderCount[j] -= pairs;
            }
        }
        unordered_map<long long, int> memo;
        happyGroups += dfs(remainderCount, batchSize, 0, memo);

        return happyGroups;
    }
private:
    int dfs(vector<int>& remainderCount, int batchSize, int remaining, unordered_map<long long, int>& memo) {
        long long state = 0;
        for (int count : remainderCount) {
            state = state * 50 + count;
        }
        state = state * batchSize + remaining;

        if (memo.count(state)) return memo[state];

        int maxHappy = 0;
        for (int i = 0; i < remainderCount.size(); ++i) {
            if (remainderCount[i] > 0) {
                remainderCount[i]--;
                int nextRemaining = (remaining + i) % batchSize;
                int extraHappy = (nextRemaining == 0) ? 1 : 0;
                maxHappy = max(maxHappy, extraHappy + dfs(remainderCount, batchSize, nextRemaining, memo));
                remainderCount[i]++;
            }
        }

        return memo[state] = maxHappy;
    }
};
int main() {
    int batchSize, n;
    cout << "Enter the batch size: ";
    cin >> batchSize;

    cout << "Enter the number of groups: ";
    cin >> n;

    vector<int> groups(n);
    cout << "Enter the size of each group: ";
    for (int i = 0; i < n; ++i) {
        cin >> groups[i];
    }

    DonutShop shop;
    int result = shop.maxHappyGroups(batchSize, groups);

    cout << "The maximum number of happy groups is: " << result << endl;
    return 0;
}