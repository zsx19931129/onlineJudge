class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int vlen = digits.size();
        vector<int> ret;
        int carry = 1;


        for(int i=vlen-1;i>=0;--i){
        	int cur = digits[i] + carry;
        	ret.push_back(cur%10);
        	carry = cur/10;
        }
        if(carry){
        	ret.push_back(1);
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};