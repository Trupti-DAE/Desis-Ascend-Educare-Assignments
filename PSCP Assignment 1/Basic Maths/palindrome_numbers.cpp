#include <bits/stdc++.h>
class Solution{
private:
    bool is_palindrome(string s){
        long long int low = 0, high = s.length() - 1;
        while(low < high){
            if(s[low] != s[high]) return false;
            low++;
            high--;
        }
        return true;
    }
    
    string to_binary(long long int n){
        string res = "";
        while(n){
            long long int rem = n % 2;
            res = res + char(rem + '0');
            n /= 2;
        }
        return res;
    }
    
public:
    int isPallindrome(long long int n){
        string binary = to_binary(n);
        return is_palindrome(binary) ? 1 : 0;
    }
};