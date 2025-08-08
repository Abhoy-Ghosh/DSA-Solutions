#include <iostream>
#include <vector>
#include <algorithm> // for reverse and swap
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& arr) {
        int n = arr.size();
        int indx = -1;

        // Step 1: Find first decreasing element from right
        for(int i = n - 2; i >= 0; i--){
            if(arr[i] < arr[i + 1]){
                indx = i;
                break;
            }
        }

        // Step 2: If no such index, array is last permutation
        if(indx == -1){
            reverse(arr.begin(), arr.end());
            return;
        }

        // Step 3: Find element just larger than arr[indx] from right
        for(int i = n - 1; i > indx; i--){
            if(arr[i] > arr[indx]){
                swap(arr[i], arr[indx]);
                break;
            }
        }

        // Step 4: Reverse right half
        reverse(arr.begin() + indx + 1, arr.end());
    }
};

int main() {
    Solution sol;

    vector<int> arr = {1, 2, 3}; // Example input
    cout << "Original array: ";
    for(int num : arr) cout << num << " ";
    cout << endl;

    sol.nextPermutation(arr);

    cout << "Next permutation: ";
    for(int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
