#include<bits/stdc++.h>
using namespace std;


int main(){

    char str[] =  "hello world";
    int hash[256]={0};
    for (int i =0; str[i]; i++ ){       // for ( i = 0 ; i < str.siz() ; i++){hash[str[i]- 'a']++} //we subtract 'a' as in that case we can declare hash[26]instead of hash[255]
        hash[str[i]]++;
    }

    int q;
    cout << "enter the number of queries: ";
    cin >> q;

    while(q--){
     char c;
        cout<< "character: ";
        cin >> c;
        cout << c << ':' <<  hash[c]<< endl;
    }
 return 0;
}