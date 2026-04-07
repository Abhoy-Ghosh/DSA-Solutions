#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[] = {20,5,15,5,7,4,28,6};

    int n =  sizeof(arr)/sizeof(int);
     int small = arr[0];

    for(int i = 1; i<= n; i++){
        if(arr[i] < small){
            small = arr[i];
        }
    }

    // cout<< n;
    cout<< small;
    return 0;
}