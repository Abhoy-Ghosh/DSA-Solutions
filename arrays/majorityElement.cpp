#include <iostream>
#include <vector>
#include <map>
using namespace std;

int majorityElement(vector<int>& nums) {
    int n = nums.size();
    map<int, int> numsMap;

    // Frequency count
    for (int i = 0; i < n; i++) {
        numsMap[nums[i]]++;
    }

    // Find majority (> n/2) as given in the question
    for (auto m : numsMap) {
        if (m.second > n / 2) {
            return m.first;
        }
    }

    return 0; // Return 0 if no majority found 
}

int main() {
    vector<int> nums = {3, 3, 4, 2, 3, 3, 3};

    cout << "Input array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    int result = majorityElement(nums);

    cout << "Majority element (> n/2): " << result << endl;

    return 0;
}
