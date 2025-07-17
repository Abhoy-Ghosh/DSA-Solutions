#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; 
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n ; i++) {
        cin >> arr[i];  
    }

    // Precompute frequencies
    map<int, int> mpp;
    for (int i = 0; i < n ; i++) {
        mpp[arr[i]]++;
    }

    int q;
    cout << "Enter number of queries: ";
    cin >> q;

    while (q--) {
        int number;
        cout << "Enter the number: ";
        cin >> number;

        // Fetch frequency
        cout << number << " -> " << mpp[number] << endl;
    }

    return 0;
}


