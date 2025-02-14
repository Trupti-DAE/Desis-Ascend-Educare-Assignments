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
    int x;
    cin >> x;
    arr.erase(arr.begin() + x - 1);
    int a, b;
    cin >> a >> b;
    arr.erase(arr.begin() + a - 1, arr.begin() + b - 1);
    cout << arr.size() << endl;
    for(int i : arr) cout << i << " ";
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
