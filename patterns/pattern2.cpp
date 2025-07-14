#include<bits/stdc++.h>
using namespace std;

void print2(int n){
    for(int i = 1; i <= 2*n-1; i++){
        int stars = i;
        // if(i <= n){
        //     for(int j = 1; j<= stars; j++){cout << "* ";};
        // }
        if(i > n){stars = 2*n-i;}
            for(int j = 1; j<= stars; j++){cout << "* ";};
    cout << endl;
    }
}

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
    int n;
        cout << "enter the value of n : " ;
        cin >> n ;
        print2(n);
    }
  return 0; 
}