#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int maxArea(vector<int>& height) {
    int maxWater = 0;
    int left = 0, right = height.size() - 1;
    while (left < right) {
        int width = right - left;
        int currentHeight = min(height[left], height[right]);
        int currentWater = width * currentHeight;

        maxWater = max(maxWater, currentWater);

        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxWater;
}
int main() {
    int n;
    cout << "Enter the number of vertical lines: ";
    cin >> n;
    vector<int> height(n);
    cout << "Enter the heights of the lines: ";
    for (int i = 0; i < n; ++i) {
        cin >> height[i];
    }
    int result = maxArea(height);
    cout << "The maximum amount of water the container can store is: " << result << endl;
    return 0;
}