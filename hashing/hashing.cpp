#include<bits/stdc++.h>
using namespace std;

int main() {
    // enter elementds in the array
    int n;
    cout << "Enter number of elements in the array: ";
    cin >> n;
    int arr[n] ;
    cout << "enter the elements one by one: "<< endl;
    for(int i = 0; i < n; i++){
        cin>> arr[i];
    }

    // Precompute
    int hash[13] = {0};
    for(int i = 0; i < n; i++){
        hash[arr[i]] += 1;
    }

    // fetch
    int q;
    cout<< "enter the query values: ";
    cin >> q;
    while (q--){
        int number;
        cin >> number;
        cout <<number<< ":" << hash[number]<< endl;
    }
    return 0;
}