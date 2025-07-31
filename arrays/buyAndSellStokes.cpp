#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int prevProfit = 0;
        int n = prices.size();

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                int currProfit = prices[j] - prices[i];
                if(currProfit < 0){
                    i = j;
                    j += 1;
                }
                else{
                    if(currProfit > prevProfit){
                        prevProfit = currProfit;
                    }
                }
            }
        }

        return prevProfit;
    }
};

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4}; 
    Solution sol;
    int profit = sol.maxProfit(prices);
    cout << "Max Profit: " << profit << endl;
    return 0;
}