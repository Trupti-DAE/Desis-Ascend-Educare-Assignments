#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    void print_divisors(int n) {
        vector<int> store;
        for(int i = 1; i * i <= n; i++){
            if(n % i == 0){
                cout << i << " ";
                if(i != (n / i)) store.push_back(n / i);
            }
        }
        for(int i = store.size() - 1; i >= 0; i--){
            cout << store[i] << " ";
        }
    }
};