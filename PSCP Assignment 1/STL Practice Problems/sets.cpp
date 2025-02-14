#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    int q;
    cin >> q;
    set<int> s;
    while(q--){
        int a, b;
        cin >> a >> b;
        if(a == 1) s.insert(b);
        else if(a == 2) s.erase(b);
        else if(a == 3){
            if(s.find(b) != s.end()) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}