class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int vlen = nums.size();
        if(vlen == 0){
        	return 0;
        }
        vector<int> dp(vlen, 0);
        dp[0] = nums[0];
        int max = dp[0];
        for(int i=1;i<vlen;++i){
 			int tmp = dp[i-1] + nums[i];
        	dp[i] = (tmp >= nums[i]) ? tmp : nums[i];
        	if(dp[i]>max){
        		max = dp[i];
        	}
        }
        return max;
    }
};