#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int k = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                nums[k++] = nums[i];
            }
        }

        return k;
    }
};

int main() {
    Solution sol;

    // Example test input
    vector<int> nums = {1, 1, 2, 3, 3, 4};

    int k = sol.removeDuplicates(nums);

    cout << "Unique count: " << k << endl;
    cout << "Modified array: ";
    for (int i = 0; i < k; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}
