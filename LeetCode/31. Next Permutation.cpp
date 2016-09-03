class Solution {
public:
    inline void swapPair(int &a, int &b){
        int tmp = a;
        a = b;
        b = tmp;
    }
    inline void reverse(int start, int end, vector<int>& nums){
        for(int i=start, j=end;i<j;++i, --j){
            swapPair(nums[i], nums[j]);
        }
    }
    void nextPermutation(vector<int>& nums) {
        int vlen = nums.size();
        int idx = -1;
        bool end = false;
        for(int i=vlen-1;i>=0;--i){
            for(int j=vlen-1;j>i;--j){
                if(nums[i]<nums[j]){
                    swapPair(nums[i], nums[j]);
                    idx = i;
                    reverse(idx+1, vlen-1, nums);
                    return ;
                }
            }
        }
        for(int i=idx+1, j=vlen-1;i<j;++i, --j){
            swapPair(nums[i], nums[j]);
        }
    }
};