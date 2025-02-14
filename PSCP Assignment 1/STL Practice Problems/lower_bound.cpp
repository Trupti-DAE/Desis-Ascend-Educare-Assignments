#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    int q;
    cin >> q;
    while(q--){
        int y;
        cin >> y;
        
        auto it = lower_bound(arr.begin(), arr.end(), y);
        int index = it - arr.begin();
        
        if(index < n && arr[index] == y) cout << "Yes " << index + 1 << endl;
        else cout << "No " << index + 1 << endl;
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
