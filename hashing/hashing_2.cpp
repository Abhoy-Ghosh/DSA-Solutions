#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cout<<"enter the number of elements in the array: ";
    cin >> n;
    int arr[] = {5,8,6,7,2,2,1,8,4,9};

    int hasharr[n] ={0};
    for (int i = 0; i< n; i++){
        hasharr[arr[i]]+=1;
    }

    int q;
    cout <<"enter the number of queries:";
    cin >> q;
    while (q--){
        int num;
        cin >> num;

        cout << num << ":" << hasharr[num]<< endl;
    
    }
    return 0;
}