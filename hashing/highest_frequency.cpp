#include<bits/stdc++.h>
using namespace std;

int main(){
    string str= "hello world";

    unordered_map<char,int> hash_map;

    for (int i  = 0;  i < str.size(); i++){
        hash_map[str[i]]++;
    }


    int maxFreq =0,  minFreq = str.size();
    char maxFreqEle, minFreqEle;

    for (auto i : hash_map){
        int count = i.second;

        if(count > maxFreq){
            maxFreq = count;
            maxFreqEle = i.first;
        }
    }
        cout<< maxFreqEle <<" ele with highest frequency : "<< maxFreq<< endl;

    int q;
    cout<<"enter number of queries: ";
    cin >> q;
    while(q--)
    {
    char c;
    cout<<"character: ";
    cin>> c;
    cout<< c << "->"<< hash_map[c]<< endl;
    
     }
    return 0;

}