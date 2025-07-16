#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cout << "enter the string: ";
    cin >> s;
// pre compute
    int hash[256] = {0};
    for(int i = 0; i < s.size() ; i++){
        hash[s[i]]++;
    }

    int q;
    cin  >> q;
    while (q--)
    {
    char c;
    cout << "enter total number of query: ";
    cin >> c;
    cout << c <<":"<< hash[c] << endl;
   }
    
   return 0;
}