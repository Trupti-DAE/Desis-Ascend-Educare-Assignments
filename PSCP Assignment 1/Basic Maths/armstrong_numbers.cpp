class Solution {
public:
    bool armstrongNumber(int n) {
        int temp = n, sum = 0;
        while(temp){
            int rem = temp % 10;
            sum += (rem * rem * rem);
            if(sum > n) return false;
            temp /= 10; 
        }
        return (sum == n);
    }
};