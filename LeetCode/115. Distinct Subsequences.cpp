class Solution {
public:
    int numDistinct(string s, string t) {
        int slen = s.length(), tlen = t.length();
        if(slen == 0 || tlen == 0){
        	return 0;
        }
        vector<vector<int>> dp(tlen, vector<int>(slen, 0));
        dp[0][0] = (s[0] == t[0]) ? 1 : 0;
        for(int i=1;i<slen;++i){
        	if(t[0] == s[i]){
        		dp[0][i] = dp[0][i-1] + 1;
        	}else{
        		dp[0][i] = dp[0][i-1];
        	}
        }
        for(int i=1;i<tlen;++i){
        	dp[i][0] = 0;
        }
        for(int i=1;i<tlen;++i){
        	for(int j=1;j<slen;++j){
        		if(s[j] == t[i]){
        			dp[i][j] = dp[i][j-1] + dp[i-1][j-1];
        		}else{
        			dp[i][j] = dp[i][j-1];
        		}
        	}
        }
        return dp[tlen-1][slen-1];
    }
};