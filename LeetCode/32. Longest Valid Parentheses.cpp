class Solution {
public:
    int longestValidParentheses(string s) {
        int slen = s.length();
        vector<int> dp(slen, 0);
        int stack=0;
        int retVal=0;
        for(int i=0;i<slen;++i){
            if(s[i] == '('){
                ++stack;
            }else{
                if(stack>0){
                    --stack;
                    dp[i] = dp[i-1]+2;
                    if(i-dp[i]>0){
                        dp[i] += dp[i-dp[i]];
                    }
                    if(dp[i] > retVal){
                        retVal = dp[i];
                    }
                }               
            }
        }
        return retVal;
    }
};