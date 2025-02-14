#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        int curr_diff = abs(n - m);
        if(curr_diff <= k) cout << 0 << endl;
        else cout << curr_diff - k << endl;
    }
    return 0;
	// your code goes here
}