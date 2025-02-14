#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    int q;
    cin >> q;
    map<string, int> m1;
    while(q--){
        string name;
        int x;
        cin >> x >> name;
        if(x == 1){
            int marks;
            cin >> marks;
            m1[name] += marks;
        }
        else if(x == 2){
            m1.erase(name);
        }
        else if(x == 3){
            cout << m1[name] << endl;
        }
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}