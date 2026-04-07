#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[] = {20,5,15,5,7,4,28,6};

    int n = sizeof(arr)/sizeof(int);
    
     
        int minIdx;

        for(int i  = 0; i < n ; i++){
            minIdx =  i;

            for (int j = i; j < n; j++){
                if(arr[minIdx] > arr[j]){
                    minIdx = j;
                }
            }

            // if(minIndex != i){
            // swap(arr[i], arr[minIndex]);
            // } edge case of swap : if i == minIndex no need swap 


            swap(arr[i],arr[minIdx]);
        }



    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }


    return 0; 
}

//Selection Sort = Fix position i by finding minimum from i → n-1

// i = current position to fix
// j = search smallest in remaining array

// Left side (0 → i-1) = already sorted ✅
// Right side (i → n-1) = unsorted ❌ So only search in unsorted part.

// Time: O(n²) (always)
// Space: O(1)
// Not stable ❌